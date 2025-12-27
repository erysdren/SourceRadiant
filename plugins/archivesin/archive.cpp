/*
   Copyright (C) 2001-2006, William Joseph.
   All Rights Reserved.

   This file is part of GtkRadiant.

   GtkRadiant is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   GtkRadiant is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GtkRadiant; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "archive.h"

#include "idatastream.h"
#include "commandlib.h"
#include "bytestreamutils.h"
#include <algorithm>
#include "stream/filestream.h"

#include "iarchive.h"

#include "archivelib.h"

#include "plugin.h"

#include <map>
#include "string/string.h"
#include "fs_filesystem.h"

struct sinpakheader_t
{
	char magic[4]; // Name of the new PAK format ("SPAK")
	uint32_t diroffset; // Position of PAK directory from start of file
	uint32_t dirsize; // Number of entries * 0x80 (128 bytes)
};

struct sinpakentry_t
{
	char filename[0x78]; // Name of the file, Unix style, with extension, 120 chars, padded with '\0'.
	uint32_t offset; // Position of the entry in PAK file
	uint32_t size;   // Size of the entry in PAK file
};

inline void buffer_findreplace( char* buffer, char find, char replace ){
	while ( *buffer != '\0' )
	{
		if ( *buffer == find ) {
			*buffer = replace;
		}
		++buffer;
	}
}

class SinPakArchive final : public Archive
{
	class SinPakRecord
	{
	public:
		SinPakRecord( uint32_t position, uint32_t stream_size )
			: m_position( position ), m_stream_size( stream_size ){
		}
		uint32_t m_position;
		uint32_t m_stream_size;
	};
	typedef GenericFileSystem<SinPakRecord> SinPakFileSystem;
	SinPakFileSystem m_filesystem;
	FileInputStream m_pakfile;
	CopiedString m_name;

public:

	SinPakArchive( const char* name )
		: m_pakfile( name ), m_name( name ){
		if ( !m_pakfile.failed() ) {
			sinpakheader_t header;

			m_pakfile.read( reinterpret_cast<FileInputStream::byte_type*>( header.magic ), 4 );
			header.diroffset = istream_read_uint32_le( m_pakfile );
			header.dirsize = istream_read_uint32_le( m_pakfile );

			if ( strncmp( header.magic, "SPAK", 4 ) == 0 ) {
				m_pakfile.seek( header.diroffset );

				for ( uint32_t i = 0; i < header.dirsize; i += sizeof( sinpakentry_t ) )
				{
					sinpakentry_t entry;

					m_pakfile.read( reinterpret_cast<FileInputStream::byte_type*>( entry.filename ), sizeof(entry.filename) );
					entry.offset = istream_read_uint32_le( m_pakfile );
					entry.size = istream_read_uint32_le( m_pakfile );

					buffer_findreplace( entry.filename, '\\', '/' );

					SinPakFileSystem::entry_type& file = m_filesystem[entry.filename];
					if ( !file.is_directory() ) {
						globalWarningStream() << "Warning: pak archive " << Quoted( m_name ) << " contains duplicated file: " << Quoted( entry.filename ) << '\n';
					}
					else
					{
						file = new SinPakRecord( entry.offset, entry.size );
					}
				}
			}
		}
	}

	~SinPakArchive(){
		for ( auto& [ path, entry ] : m_filesystem )
			delete entry.file();
	}

	void release() override {
		delete this;
	}
	ArchiveFile* openFile( const char* name ) override {
		SinPakFileSystem::iterator i = m_filesystem.find( name );
		if ( i != m_filesystem.end() && !i->second.is_directory() ) {
			SinPakRecord* file = i->second.file();
			return StoredArchiveFile::create( name, m_name.c_str(), file->m_position, file->m_stream_size, file->m_stream_size );
		}
		return 0;
	}
	virtual ArchiveTextFile* openTextFile( const char* name ) override {
		SinPakFileSystem::iterator i = m_filesystem.find( name );
		if ( i != m_filesystem.end() && !i->second.is_directory() ) {
			SinPakRecord* file = i->second.file();
			return StoredArchiveTextFile::create( name, m_name.c_str(), file->m_position, file->m_stream_size );
		}
		return 0;
	}
	bool containsFile( const char* name ) override {
		SinPakFileSystem::iterator i = m_filesystem.find( name );
		return i != m_filesystem.end() && !i->second.is_directory();
	}
	void forEachFile( VisitorFunc visitor, const char* root ) override {
		m_filesystem.traverse( visitor, root );
	}
};


Archive* OpenArchive( const char* name ){
	return new SinPakArchive( name );
}
