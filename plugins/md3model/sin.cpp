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

#include "mdl.h"

#include "ifilesystem.h"
#include "imodel.h"

#include "imagelib.h"
#include "bytestreamutils.h"

#include "model.h"
#include "ident.h"
#include "mdlnormals.h"
#include "stringio.h"
#include "archivelib.h"

scene::Node& SiNModel_default(){
	auto *modelNode = new ModelNode();
	Model_constructNull( modelNode->model() );
	return modelNode->node();
}

const unsigned char DEF_IDENT[4] = { 'S', 'D', 'E', 'F', };

/*
========================================================================

SIN specific model formats

========================================================================
*/
const unsigned char SINBASEMODEL_HEADER[4] = { 'S', 'B', 'M', ' ' };
#define SINBASEMODEL_VERSION 1

const unsigned char SINANIMMODEL_HEADER[4] = { 'S', 'A', 'M', ' ' };
#define SINANIMMODEL_VERSION 1

typedef struct dsinanim_s
{
   int         ident;
   int         version;

   char        name[64];
   float       scale[3];      // multiply byte verts by this
   float       translate[3];  // then add this

   float       totaldelta[3]; // total displacement of this animation
   float       totaltime;

   int         num_xyz;
   int         num_frames;
   int         ofs_frames;
   int         ofs_end;      // end of file
} dsinanim_t;

void istream_read_samHeader( InputStream& inputStream, dsinanim_t& header ){
	inputStream.read( (byte *) &header.ident, 4 );
	header.version = istream_read_int32_le( inputStream );
	inputStream.read( (byte *) &header.name, sizeof(header.name) );
	header.scale[0] = istream_read_float32_le( inputStream );
	header.scale[1] = istream_read_float32_le( inputStream );
	header.scale[2] = istream_read_float32_le( inputStream );
	header.translate[0] = istream_read_float32_le( inputStream );
	header.translate[1] = istream_read_float32_le( inputStream );
	header.translate[2] = istream_read_float32_le( inputStream );
	header.totaldelta[0] = istream_read_float32_le( inputStream );
	header.totaldelta[1] = istream_read_float32_le( inputStream );
	header.totaldelta[2] = istream_read_float32_le( inputStream );
	header.totaltime = istream_read_float32_le( inputStream );
	header.num_xyz = istream_read_int32_le( inputStream );
	header.num_frames = istream_read_int32_le( inputStream );
	header.ofs_frames = istream_read_int32_le( inputStream );
	header.ofs_end = istream_read_int32_le( inputStream );
}

typedef struct dsinstvert_s
{
   float s;
   float t;
} dsinstvert_t;

void istream_read_sbmSt( InputStream& inputStream, dsinstvert_t& st ){
	st.s = istream_read_float32_le( inputStream );
	st.t = istream_read_float32_le( inputStream );
}

typedef struct dsintriangle_s
{
   short       index_xyz[3];
   short       index_st[3];
   int         id;
} dsintriangle_t;

void istream_read_sbmTriangle( InputStream& inputStream, dsintriangle_t& triangle ){
	triangle.index_xyz[0] = istream_read_int16_le( inputStream );
	triangle.index_xyz[1] = istream_read_int16_le( inputStream );
	triangle.index_xyz[2] = istream_read_int16_le( inputStream );
	triangle.index_st[0] = istream_read_int16_le( inputStream );
	triangle.index_st[1] = istream_read_int16_le( inputStream );
	triangle.index_st[2] = istream_read_int16_le( inputStream );
	triangle.id = istream_read_int32_le( inputStream );
}

typedef struct
{
	byte v[3];              // scaled byte to fit in frame mins/maxs
	byte lightnormalindex;
} md2XyzNormal_t;

void istream_read_samXyzNormal( InputStream& inputStream, md2XyzNormal_t& xyz ){
	inputStream.read( xyz.v, 3 );
	inputStream.read( &xyz.lightnormalindex, 1 );
}

typedef struct dsintriframe_s
{
   float       movedelta[3];  // used for driving the model around
   float       frametime;
   float       scale[3];      // multiply byte verts by this
   float       translate[3];  // then add this
   int         ofs_verts;
} dsintriframe_t;

void istream_read_samFrame( InputStream& inputStream, dsintriframe_t& frame ){
	frame.movedelta[0] = istream_read_float32_le( inputStream );
	frame.movedelta[1] = istream_read_float32_le( inputStream );
	frame.movedelta[2] = istream_read_float32_le( inputStream );
	frame.frametime = istream_read_float32_le( inputStream );
	frame.scale[0] = istream_read_float32_le( inputStream );
	frame.scale[1] = istream_read_float32_le( inputStream );
	frame.scale[2] = istream_read_float32_le( inputStream );
	frame.translate[0] = istream_read_float32_le( inputStream );
	frame.translate[1] = istream_read_float32_le( inputStream );
	frame.translate[2] = istream_read_float32_le( inputStream );
	frame.ofs_verts = istream_read_int32_le( inputStream );
}

typedef struct dsinbasemdl_s
{
   int            ident;
   int            version;

   int            num_xyz;
   int            num_st;       // greater than num_xyz for seams
   int            num_groups;

   int            ofs_st;       // byte offset from start for stverts
   int            ofs_end;      // end of file
} dsinbasemdl_t;

void istream_read_sbmHeader( InputStream& inputStream, dsinbasemdl_t& header ){
	inputStream.read( (byte *) &header.ident, 4 );
	header.version = istream_read_int32_le( inputStream );
	header.num_xyz = istream_read_int32_le( inputStream );
	header.num_st = istream_read_int32_le( inputStream );
	header.num_groups = istream_read_int32_le( inputStream );
	header.ofs_st = istream_read_int32_le( inputStream );
	header.ofs_end = istream_read_int32_le( inputStream );
}

typedef struct dsintrigroup_s
{
   int         id;
   int         num_tris;
   int         num_glcmds;   // dwords in strip/fan command list
   int         ofs_glcmds;
   int         ofs_tris;
   int         ofs_end;
} dsintrigroup_t;

void istream_read_sbmTriGroup( InputStream& inputStream, dsintrigroup_t& header ){
	header.id = istream_read_int32_le( inputStream );
	header.num_tris = istream_read_int32_le( inputStream );
	header.num_glcmds = istream_read_int32_le( inputStream );
	header.ofs_glcmds = istream_read_int32_le( inputStream );
	header.ofs_tris = istream_read_int32_le( inputStream );
	header.ofs_end = istream_read_int32_le( inputStream );
}

ArbitraryMeshVertex SiNVertex_construct(float scale, Vector3 origin, const dsintriframe_t* pFrame, const md2XyzNormal_t* xyz, const dsinstvert_t *st ){
	return ArbitraryMeshVertex(
	           Vertex3f(
	               xyz->v[0] * scale * pFrame->scale[0] + (pFrame->translate[0] + origin[0]),
	               xyz->v[1] * scale * pFrame->scale[1] + (pFrame->translate[1] + origin[1]),
	               xyz->v[2] * scale * pFrame->scale[2] + (pFrame->translate[2] + origin[2])
	           ),
	           Normal3f(
	               g_mdl_normals[xyz->lightnormalindex][0],
	               g_mdl_normals[xyz->lightnormalindex][1],
	               g_mdl_normals[xyz->lightnormalindex][2]
	           ),
	           TexCoord2f(
	               st->s,
	               st->t
	           )
	       );
}

void SiNSurface_read( Model& model, ScopedArchiveBuffer& sbmFile, ScopedArchiveBuffer& samFile, float scale, Vector3 origin, std::string skinname ){
	Surface& surface = model.newSurface();
	dsinbasemdl_t sbmHeader;
	{
		PointerInputStream b(sbmFile.buffer);
		istream_read_sbmHeader( b, sbmHeader );
	}

	Array<dsintrigroup_t> groups;
	Array<Array<dsintriangle_t>> triangles;
	Array<dsinstvert_t> st;

	size_t num_tris = 0;

	{
		PointerInputStream b(sbmFile.buffer + sizeof(dsinbasemdl_t));
		groups.resize(sbmHeader.num_groups);

		for (int i = 0; i < sbmHeader.num_groups; i++)
			istream_read_sbmTriGroup( b, groups[i] );
	}

	{
		triangles.resize(sbmHeader.num_groups);

		for (int i = 0; i < sbmHeader.num_groups; i++)
		{
			num_tris += groups[i].num_tris;
			triangles[i].resize(groups[i].num_tris);

			PointerInputStream b((sbmFile.buffer + sizeof(dsinbasemdl_t) + (sizeof(dsintrigroup_t) * i)) + groups[i].ofs_tris);

			for (int t = 0; t < groups[i].num_tris; t++)
				istream_read_sbmTriangle( b, triangles[i][t] );
		}
	}

	{
		st.resize(sbmHeader.num_st);

		PointerInputStream b(sbmFile.buffer + sbmHeader.ofs_st);

		for (int i = 0; i < sbmHeader.num_st; i++)
			istream_read_sbmSt( b, st[i] );
	}

	dsinanim_t samHeader;
	{
		PointerInputStream b(samFile.buffer);
		istream_read_samHeader( b, samHeader );
	}

	// we only care about frame 0
	dsintriframe_t frame;
	Array<md2XyzNormal_t> vertices;

	{
		PointerInputStream b(samFile.buffer + samHeader.ofs_frames);
		istream_read_samFrame(b, frame);
	}

	{
		PointerInputStream b(samFile.buffer + samHeader.ofs_frames + frame.ofs_verts);
		vertices.resize(samHeader.num_xyz);

		for (int i = 0; i < samHeader.num_xyz; i++)
			istream_read_samXyzNormal( b, vertices[i] );
	}

	{
		surface.indices().reserve( num_tris * 3 );

		UniqueVertexBuffer<ArbitraryMeshVertex> inserter( surface.vertices() );
		inserter.reserve( sbmHeader.num_st );

		for (int i = 0; i < groups.size(); i++)
			for ( int t = 0; t < groups[i].num_tris; ++t )
			{
				surface.indices().insert( inserter.insert( SiNVertex_construct( scale, origin, &frame, &vertices[triangles[i][t].index_xyz[0]], &st[triangles[i][t].index_st[0]] ) ) );
				surface.indices().insert( inserter.insert( SiNVertex_construct( scale, origin, &frame, &vertices[triangles[i][t].index_xyz[1]], &st[triangles[i][t].index_st[1]] ) ) );
				surface.indices().insert( inserter.insert( SiNVertex_construct( scale, origin, &frame, &vertices[triangles[i][t].index_xyz[2]], &st[triangles[i][t].index_st[2]] ) ) );
			}
	}

	surface.setShader( skinname.c_str() );
	surface.updateAABB();
}

void SiNModel_read( Model& model, ScopedArchiveBuffer& sbmFile, ScopedArchiveBuffer& samFile, float scale, Vector3 origin, std::string skinname ){
	SiNSurface_read( model, sbmFile, samFile, scale, origin, skinname );
	model.updateAABB();
}

scene::Node& SiNModel_new( ScopedArchiveBuffer& sbmFile, ScopedArchiveBuffer& samFile, float scale, Vector3 origin, std::string skinname ){
	auto *modelNode = new ModelNode();
	SiNModel_read( modelNode->model(), sbmFile, samFile, scale, origin, skinname );
	return modelNode->node();
}

scene::Node& SiNModel_fromBuffer( ArchiveFile& file ){

	unsigned char magic[4];
	file.getInputStream().read((unsigned char *) &magic, 4);

	if (!ident_equal(magic, DEF_IDENT)) {
		return SiNModel_default();
	}

	BinaryToTextInputStream<InputStream> stream(file.getInputStream());
	
	Tokeniser& tokeniser = GlobalScriptLibrary().m_pfnNewSimpleTokeniser( stream );
	tokeniser.nextLine();

	// temp stuff
	std::string model;
	std::string path;
	std::string skin;
	std::string anim;
	float scale = 1.0f;
	Vector3 origin = { 0.0f, 0.0f, 0.0f };

	while (true)
	{
		int argc = 0;
		std::string tokens[32];

		tokens[argc++] = tokeniser.getToken();
		size_t line = tokeniser.getLine();

		while (true)
		{
			const char *tok;

			if (!(tok = tokeniser.getToken()))
				break;
			else if (tokeniser.getLine() != line)
			{
				tokeniser.ungetToken();
				break;
			}

			tokens[argc++] = tok;
		}

		if (tokens[0].empty())
			break;
		else if (tokens[0].starts_with('!'))
			break;
		else if (string_equal_nocase(tokens[0].c_str(), "path"))
			path = tokens[1];
		else if (string_equal_nocase(tokens[0].c_str(), "scale"))
			scale = atof(tokens[1].c_str());
		else if (string_equal_nocase(tokens[0].c_str(), "origin"))
		{
			origin[0] = atof(tokens[1].c_str());
			origin[1] = atof(tokens[2].c_str());
			origin[2] = atof(tokens[3].c_str());
		}
		else if (string_equal_suffix_nocase(tokens[argc - 1].c_str(), ".sbm"))
		{
			if (model.empty())
				model = tokens[argc - 1];
		}
		else if (string_equal_suffix_nocase(tokens[argc - 1].c_str(), ".tga"))
		{
			if (skin.empty())
				skin = tokens[argc - 1];
		}
		else if (string_equal_suffix_nocase(tokens[argc - 1].c_str(), ".sam"))
		{
			if (anim.empty())
				anim = tokens[argc - 1];
		}
	}

	if (model.empty())
		model = std::string(std::string_view{PathFilename(file.getName()).begin(), PathFilename(file.getName()).end()}) + ".sbm";
	if (path.empty())
		path = std::string_view{PathExtensionless(file.getName()).begin(), PathExtensionless(file.getName()).end()};

	{
		std::string sbm = path + "/" + model;
		ArchiveFile *sbmFile = GlobalFileSystem().openFile(sbm.c_str());
		std::string sam = path + "/" + anim;
		ArchiveFile *samFile = GlobalFileSystem().openFile(sam.c_str());

		if (sbmFile && samFile)
		{
			ScopedArchiveBuffer sbmBuffer(*sbmFile);
			ScopedArchiveBuffer samBuffer(*samFile);
			return SiNModel_new(sbmBuffer, samBuffer, scale, origin, path + "/" + skin);
		}

		if (samFile)
			samFile->release();
		if (sbmFile)
			sbmFile->release();
	}

	tokeniser.release();

	return SiNModel_default();
}

scene::Node& loadSiNModel( ArchiveFile& file ){
	return SiNModel_fromBuffer( file );
}
