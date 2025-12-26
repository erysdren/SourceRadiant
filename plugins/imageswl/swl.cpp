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

#include "swl.h"

#include "ifilesystem.h"

#include "os/path.h"
#include "stream/stringstream.h"
#include "bytestreamutils.h"
#include "imagelib.h"

typedef struct swl {
	char name[64];
	uint32_t width;
	uint32_t height;
	uint8_t palette[256][4];
	uint32_t palcrc;
	uint32_t offsets[4];
	char animname[64];
	uint32_t flags;
	uint32_t contents;
	uint16_t value;
	uint16_t direct;
	float animtime;
	float nonlit;
	uint16_t directangle;
	uint16_t trans_angle;
	float directstyle;
	float translucence;
	float friction;
	float restitution;
	float trans_mag;
	float color[3];
} swl_t;

Image* LoadSwl( ArchiveFile& file ){
	ScopedArchiveBuffer buffer( file );

	swl_t* swl = (swl_t*)buffer.buffer;

	Image* image = new RGBAImageFlags( swl->width, swl->height, swl->flags, swl->contents, swl->value );

	byte* src = buffer.buffer + swl->offsets[0];
	byte* dest = image->getRGBAPixels();
	for (uint32_t y = 0; y < swl->height; y++)
	{
		for (uint32_t x = 0; x < swl->width; x++)
		{
			dest[0] = swl->palette[*src][0];
			dest[1] = swl->palette[*src][1];
			dest[2] = swl->palette[*src][2];
			dest[3] = 255;

			src += 1;
			dest += 4;
		}
	}

	return image;
}
