/*
   Copyright (C) 1999-2006 Id Software, Inc. and contributors.
   For a list of contributors, see the accompanying CONTRIBUTORS file.

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

#include "files.h"
#include "mainframe.h"
#include "os/file.h"
#include "stream/stringstream.h"

#include <QFile>

QFile* Radiant_OpenFileRead(const char *path)
{
	auto diskpath = StringStream( GlobalRadiant().getAppPath(), path );

	// check on disk first
	if (file_exists(diskpath))
	{
		QFile* file = new QFile(diskpath.c_str());

		if (!file->open(QIODevice::ReadOnly))
		{
			delete file;
			return nullptr;
		}

		return file;
	}

	// then check resources
	auto respath = StringStream( ":/", path );
	QFile* file = new QFile(respath.c_str());
	if (!file->open(QIODevice::ReadOnly))
	{
		delete file;
		return nullptr;
	}

	return file;
}

void Radiant_CloseFile(QFile *file)
{
	file->close();
	delete file;
}
