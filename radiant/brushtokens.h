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

#pragma once

#include "stringio.h"
#include "stream/stringstream.h"
#include "brush.h"

inline bool FaceShader_importContentsFlagsValue( FaceShader& faceShader, Tokeniser& tokeniser ){
	// parse the optional contents/flags/value
	RETURN_FALSE_IF_FAIL( Tokeniser_getInteger( tokeniser, faceShader.m_flags.m_contentFlags ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getInteger( tokeniser, faceShader.m_flags.m_surfaceFlags ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getInteger( tokeniser, faceShader.m_flags.m_value ) );
	return true;
}

#include <cstdint>

template<typename T>
struct name_and_flag_t
{
    const char  *name;
    T           flag;
};

// extra SiN info
// TODO: move this stuff to gamedef in some way
enum class sin_contents_t : uint32_t
{
    SOLID     = 0x1,
    WINDOW    = 0x2,
    FENCE     = 0x4,
    LAVA      = 0x8,
    SLIME     = 0x10,
    WATER     = 0x20,
    MIST      = 0x40,
    // UNUSED = 0x80,
    
    // UNUSED = 0x100,
    // UNUSED = 0x200,
    // UNUSED = 0x400,
    // UNUSED = 0x800,
    // UNUSED = 0x1000,
    // UNUSED = 0x2000,
    // UNUSED = 0x4000,
    // UNUSED = 0x8000,
    
    PLAYERCLIP   = 0x10000,
    MONSTERCLIP  = 0x20000,
    CURRENT_0    = 0x40000,
    CURRENT_90   = 0x80000,
    CURRENT_180  = 0x100000,
    CURRENT_270  = 0x200000,
    CURRENT_UP   = 0x400000,
    CURRENT_DOWN = 0x800000,

    ORIGIN      = 0x1000000,
    MONSTER     = 0x2000000,
    CORPSE      = 0x4000000,
    DETAIL      = 0x8000000,
    TRANSLUCENT = 0x10000000,
    LADDER      = 0x20000000
    // UNUSED   = 0x40000000,
    // UNUSED   = 0x80000000,
};

static constexpr name_and_flag_t<sin_contents_t> sin_contents_names[] = {
    {"solid",         sin_contents_t::SOLID},
    {"window",        sin_contents_t::WINDOW},
    {"fence",         sin_contents_t::FENCE},
    {"lava",          sin_contents_t::LAVA},
    {"slime",         sin_contents_t::SLIME},
    {"water",         sin_contents_t::WATER},
    {"mist",          sin_contents_t::MIST},

    {"playerclip",    sin_contents_t::PLAYERCLIP},
    {"monsterclip",   sin_contents_t::MONSTERCLIP},
    {"current_0",     sin_contents_t::CURRENT_0},
    {"current_90",    sin_contents_t::CURRENT_90},
    {"current_180",   sin_contents_t::CURRENT_180},
    {"current_270",   sin_contents_t::CURRENT_270},
    {"current_up",    sin_contents_t::CURRENT_UP},
    {"current_dn",    sin_contents_t::CURRENT_DOWN},
    
    {"origin",        sin_contents_t::ORIGIN},
    {"monster",       sin_contents_t::MONSTER},
    {"corpse",        sin_contents_t::CORPSE},
    {"detail",        sin_contents_t::DETAIL},
    {"translucent",   sin_contents_t::TRANSLUCENT},
    {"ladder",        sin_contents_t::LADDER}
};

enum class sin_surfflags_t : uint32_t
{
    LIGHT    = 0x1,
    MASKED   = 0x2,
    SKY      = 0x4,
    WARP     = 0x8,
    NONLIT   = 0x10,
    NOFILTER = 0x20,
    CONVEYOR = 0x40,
    NODRAW   = 0x80,

    HINT     = 0x100,
    SKIP     = 0x200,
    WAVY     = 0x400,
    RICOCHET = 0x800,
    PRELIT   = 0x1000,
    MIRROR   = 0x2000,
    CONSOLE  = 0x4000,
    USECOLOR = 0x8000,

    HARDWAREONLY  = 0x10000,
    DAMAGE        = 0x20000,
    WEAK          = 0x40000,
    NORMAL        = 0x80000,
    ADD           = 0x100000,
    ENVMAPPED     = 0x200000,
    RANDOMANIMATE = 0x400000,
    ANIMATE       = 0x800000,
    
    RNDTIME   = 0x1000000,
    TRANSLATE = 0x2000000,
    NOMERGE   = 0x4000000,
    TYPE_BIT0 = 0x8000000,
    TYPE_BIT1 = 0x10000000,
    TYPE_BIT2 = 0x20000000,
    TYPE_BIT3 = 0x40000000,
    //UNUSED  = 0x80000000
};

static constexpr name_and_flag_t<sin_surfflags_t> sin_surfflag_names[] = {
    {"light",       sin_surfflags_t::LIGHT},
    {"masked",      sin_surfflags_t::MASKED},
    {"sky",         sin_surfflags_t::SKY},
    {"warping",     sin_surfflags_t::WARP},
    {"nonlit",      sin_surfflags_t::NONLIT},
    {"nofilter",    sin_surfflags_t::NOFILTER},
    {"conveyor",    sin_surfflags_t::CONVEYOR},
    {"nodraw",      sin_surfflags_t::NODRAW},

    {"hint",        sin_surfflags_t::HINT},
    {"skip",        sin_surfflags_t::SKIP},
    {"wavy",        sin_surfflags_t::WAVY},
    {"ricochet",    sin_surfflags_t::RICOCHET},
    {"prelit",      sin_surfflags_t::PRELIT},
    {"mirror",      sin_surfflags_t::MIRROR},
    {"console",     sin_surfflags_t::CONSOLE},
    {"usecolor",    sin_surfflags_t::USECOLOR},

    {"hardwareonly",sin_surfflags_t::HARDWAREONLY},
    {"damage",      sin_surfflags_t::DAMAGE},
    {"weak",        sin_surfflags_t::WEAK},
    {"normal",      sin_surfflags_t::NORMAL},
    {"add",         sin_surfflags_t::ADD},
    {"envmapped",   sin_surfflags_t::ENVMAPPED},
    {"random",      sin_surfflags_t::RANDOMANIMATE},
    {"animate",     sin_surfflags_t::ANIMATE},

    {"rndtime",     sin_surfflags_t::RNDTIME},
    {"translate",   sin_surfflags_t::TRANSLATE},
    {"nomerge",     sin_surfflags_t::NOMERGE},
    {"surfbit0",    sin_surfflags_t::TYPE_BIT0},
    {"surfbit1",    sin_surfflags_t::TYPE_BIT1},
    {"surfbit2",    sin_surfflags_t::TYPE_BIT2},
    {"surfbit3",    sin_surfflags_t::TYPE_BIT3},
};

template<typename T>
inline void FaceShader_SiN_AttemptParseScalar(const std::string_view key, const std::string_view value, const char *expected_key, T &scalar)
{
	if (expected_key != key) {
		return;
	}

	if constexpr(std::is_integral_v<T>)
	{
		scalar = atoi(value.data());
	}
	else
	{
		scalar = atof(value.data());
	}
}

inline void FaceShader_SiN_AttemptParseString(const std::string_view key, const std::string_view value, const char *expected_key, CopiedString &scalar)
{
	if (expected_key != key) {
		return;
	}

	scalar = value;
}

inline void FaceShader_SiN_AttemptParseVector(const std::string_view key, const std::string_view value, const char *expected_key, Vector3 &scalar)
{
	if (expected_key != key) {
		return;
	}

	char *next = (char *) value.data();

	for (int i = 0; i < 3; i++) {
		scalar[i] = strtof(next, &next);
	}
}

inline bool FaceShader_importSiNData( FaceShader& faceShader, Tokeniser& tokeniser ){
	// SiN always specifies flags.
	faceShader.m_flags.m_specified = true;

	// TODO: probably would be nice to tell the tokeniser not to
	// cross lines, and then distinguish EOL vs EOF
	while (true) {
		const char *tok = tokeniser.getToken();

		if (*tok == '-') {
			// for now skip this
			//Tokeniser_unexpectedError( tokeniser, tok, "+ or alphabet character" );
			return true;
		}

		// + or a-z means it's a valid object
		if (*tok != '+' && !isalpha(*tok)) {
			tokeniser.ungetToken();
			return true;
		}
		
		// flag
		if (*tok == '+') {
			const std::string_view flag = tok + 1;

			// TODO: use game def
			for (auto &content : sin_contents_names) {
				if (flag == content.name) {
					faceShader.m_flags.m_contentFlags |= (int) content.flag;
					break;
				}
			}
			for (auto &surf : sin_surfflag_names) {
				if (flag == surf.name) {
					faceShader.m_flags.m_surfaceFlags |= (int) surf.flag;
					break;
				}
			}

			continue;
		}

		// kvp
		std::string value;
		std::string key = tok;

		// keys cannot start with a number, so we can use that knowledge to auto-detect
		// vectors when they appear (only color, though)
		while (true) {
			tok = tokeniser.getToken();

			if (!value.empty()) {
				value += " ";
			}

			value += tok;

			tok = tokeniser.getToken();
			bool eov = !isdigit(*tok);
			tokeniser.ungetToken();

			if (eov) {
				break;
			}
		}

		// ugly but whatever
		FaceShader_SiN_AttemptParseScalar(key, value, "animtime", faceShader.m_flags.m_sinData.m_animtime);
		FaceShader_SiN_AttemptParseScalar(key, value, "friction", faceShader.m_flags.m_sinData.m_friction);
		FaceShader_SiN_AttemptParseScalar(key, value, "restitution", faceShader.m_flags.m_sinData.m_restitution);
		FaceShader_SiN_AttemptParseScalar(key, value, "direct", faceShader.m_flags.m_sinData.m_direct);
		FaceShader_SiN_AttemptParseScalar(key, value, "directangle", faceShader.m_flags.m_sinData.m_directangle);
		FaceShader_SiN_AttemptParseScalar(key, value, "translucence", faceShader.m_flags.m_sinData.m_translucence);
		FaceShader_SiN_AttemptParseScalar(key, value, "trans_mag", faceShader.m_flags.m_sinData.m_trans_mag);
		FaceShader_SiN_AttemptParseScalar(key, value, "trans_angle", faceShader.m_flags.m_sinData.m_trans_angle);
		FaceShader_SiN_AttemptParseVector(key, value, "color", faceShader.m_flags.m_sinData.m_color);
		FaceShader_SiN_AttemptParseScalar(key, value, "lightvalue", faceShader.m_flags.m_sinData.m_lightvalue);
		FaceShader_SiN_AttemptParseScalar(key, value, "nonlitvalue", faceShader.m_flags.m_sinData.m_nonlitvalue);
		FaceShader_SiN_AttemptParseString(key, value, "directstyle", faceShader.m_flags.m_sinData.m_directstylename);
	}
	return true;
}

inline bool FaceTexdef_importTokens( FaceTexdef& texdef, Tokeniser& tokeniser ){
	// parse texdef
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.shift[0] ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.shift[1] ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.rotate ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.scale[0] ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.scale[1] ) );

	if( !texdef_sane( texdef.m_projection.m_texdef ) )
		globalWarningStream() << "FaceTexdef_importTokens: bad texdef\n";

	return true;
}

inline bool FaceTexdef_BP_importTokens( FaceTexdef& texdef, Tokeniser& tokeniser ){
	// parse alternate texdef
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "(" ) );
	{
		RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "(" ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_brushprimit_texdef.coords[0][0] ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_brushprimit_texdef.coords[0][1] ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_brushprimit_texdef.coords[0][2] ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, ")" ) );
	}
	{
		RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "(" ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_brushprimit_texdef.coords[1][0] ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_brushprimit_texdef.coords[1][1] ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_brushprimit_texdef.coords[1][2] ) );
		RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, ")" ) );
	}
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, ")" ) );
	return true;
}

inline bool FaceTexdef_Valve220_importTokens( FaceTexdef& texdef, Tokeniser& tokeniser ){
	// parse texdef
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "[" ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_basis_s.x() ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_basis_s.y() ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_basis_s.z() ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.shift[0] ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "]" ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "[" ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_basis_t.x() ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_basis_t.y() ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_basis_t.z() ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.shift[1] ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "]" ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.rotate ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.scale[0] ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getFloat( tokeniser, texdef.m_projection.m_texdef.scale[1] ) );

	texdef.m_projection.m_texdef.rotate = -texdef.m_projection.m_texdef.rotate;

	if( !texdef_sane( texdef.m_projection.m_texdef ) )
		globalWarningStream() << "FaceTexdef_Valve220_importTokens: bad texdef\n";

	return true;
}

inline bool FacePlane_importTokens( FacePlane& facePlane, Tokeniser& tokeniser ){
	// parse planepts
	for ( std::size_t i = 0; i < 3; ++i )
	{
		RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "(" ) );
		for ( std::size_t j = 0; j < 3; ++j )
		{
			RETURN_FALSE_IF_FAIL( Tokeniser_getDouble( tokeniser, facePlane.planePoints()[i][j] ) );
		}
		RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, ")" ) );
	}
	facePlane.MakePlane();
	return true;
}

inline bool FacePlane_Doom3_importTokens( FacePlane& facePlane, Tokeniser& tokeniser ){
	Plane3 plane;
	// parse plane equation
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "(" ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getDouble( tokeniser, plane.a ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getDouble( tokeniser, plane.b ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getDouble( tokeniser, plane.c ) );
	RETURN_FALSE_IF_FAIL( Tokeniser_getDouble( tokeniser, plane.d ) );
	plane.d = -plane.d;
	RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, ")" ) );

	facePlane.setDoom3Plane( plane );
	return true;
}

inline bool FaceShader_Doom3_importTokens( FaceShader& faceShader, Tokeniser& tokeniser ){
	const char *shader = tokeniser.getToken();
	if ( shader == 0 ) {
		Tokeniser_unexpectedError( tokeniser, shader, "#shader-name" );
		return false;
	}
	if ( string_equal( shader, "_emptyname" ) ) {
		shader = texdef_name_default();
	}
	faceShader.setShader( shader );
	return true;
}

inline bool FaceShader_importTokens( FaceShader& faceShader, Tokeniser& tokeniser ){
	const char* texture = tokeniser.getToken();
	if ( texture == 0 ) {
		Tokeniser_unexpectedError( tokeniser, texture, "#texture-name" );
		return false;
	}
	if ( string_equal( texture, "NULL" ) ) {
		faceShader.setShader( texdef_name_default() );
	}
	else
	{
		faceShader.setShader( StringStream<64>( GlobalTexturePrefix_get(), texture ) );
	}
	return true;
}




class Doom3FaceTokenImporter
{
	Face& m_face;
public:
	Doom3FaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_Doom3_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_BP_importTokens( m_face.getTexdef(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_Doom3_importTokens( m_face.getShader(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importContentsFlagsValue( m_face.getShader(), tokeniser ) );

		m_face.getTexdef().m_projectionInitialised = true;
		m_face.getTexdef().m_scaleApplied = true;

		return true;
	}
};

class Quake4FaceTokenImporter
{
	Face& m_face;
public:
	Quake4FaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_Doom3_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_BP_importTokens( m_face.getTexdef(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_Doom3_importTokens( m_face.getShader(), tokeniser ) );

		m_face.getTexdef().m_projectionInitialised = true;
		m_face.getTexdef().m_scaleApplied = true;

		return true;
	}
};

class QuakeFaceTokenImporter
{
	Face& m_face;
public:
	QuakeFaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importTokens( m_face.getShader(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_importTokens( m_face.getTexdef(), tokeniser ) );
		// optional face flags
		// Q1: normally not present, try to load to handle 3rd party maps with them or extended format with flags
		// Q2: presence determines whether flags are considered as specified (otherwise embedded .wal flags are used)
		// Q3: normally present, load optionally to handle 3rd party maps without them
		if ( Tokeniser_nextTokenIsDigit( tokeniser ) ) {
			m_face.getShader().m_flags.m_specified = true; // enable for Q2
			RETURN_FALSE_IF_FAIL( FaceShader_importContentsFlagsValue( m_face.getShader(), tokeniser ) );
		}
		m_face.getTexdef().m_scaleApplied = true;
		return true;
	}
};

class SinFaceTokenImporter
{
	Face& m_face;
public:
	SinFaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importTokens( m_face.getShader(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_importTokens( m_face.getTexdef(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importSiNData( m_face.getShader(), tokeniser ) );
		m_face.getTexdef().m_scaleApplied = true;
		return true;
	}
};

class SinValve220FaceTokenImporter
{
	Face& m_face;
public:
	SinValve220FaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importTokens( m_face.getShader(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_Valve220_importTokens( m_face.getTexdef(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importSiNData( m_face.getShader(), tokeniser ) );
		m_face.getTexdef().m_scaleApplied = true;
		return true;
	}
};

class Quake3BPFaceTokenImporter
{
	Face& m_face;
public:
	Quake3BPFaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_BP_importTokens( m_face.getTexdef(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importTokens( m_face.getShader(), tokeniser ) );
		if ( Tokeniser_nextTokenIsDigit( tokeniser ) ) { ///optional for more flexibility
			m_face.getShader().m_flags.m_specified = true; // enable for Q2
			RETURN_FALSE_IF_FAIL( FaceShader_importContentsFlagsValue( m_face.getShader(), tokeniser ) );
		}

		m_face.getTexdef().m_projectionInitialised = true;
		m_face.getTexdef().m_scaleApplied = true;

		return true;
	}
};

class Valve220FaceTokenImporter
{
	Face& m_face;
public:
	Valve220FaceTokenImporter( Face& face ) : m_face( face ){
	}
	bool importTokens( Tokeniser& tokeniser ){
		RETURN_FALSE_IF_FAIL( FacePlane_importTokens( m_face.getPlane(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceShader_importTokens( m_face.getShader(), tokeniser ) );
		RETURN_FALSE_IF_FAIL( FaceTexdef_Valve220_importTokens( m_face.getTexdef(), tokeniser ) );
		if ( Tokeniser_nextTokenIsDigit( tokeniser ) ) { ///optional for more flexibility
			m_face.getShader().m_flags.m_specified = true; // enable for Q2
			RETURN_FALSE_IF_FAIL( FaceShader_importContentsFlagsValue( m_face.getShader(), tokeniser ) );
		}
		m_face.getTexdef().m_scaleApplied = true;
		return true;
	}
};


inline void FacePlane_Doom3_exportTokens( const FacePlane& facePlane, TokenWriter& writer ){
	// write plane equation
	writer.writeToken( "(" );
	writer.writeFloat( facePlane.getDoom3Plane().a );
	writer.writeFloat( facePlane.getDoom3Plane().b );
	writer.writeFloat( facePlane.getDoom3Plane().c );
	writer.writeFloat( -facePlane.getDoom3Plane().d );
	writer.writeToken( ")" );
}

inline void FacePlane_exportTokens( const FacePlane& facePlane, TokenWriter& writer ){
	// write planepts
	for ( std::size_t i = 0; i < 3; ++i )
	{
		writer.writeToken( "(" );
		for ( std::size_t j = 0; j < 3; ++j )
		{
			writer.writeFloat( Face::m_quantise( facePlane.planePoints()[i][j] ) );
		}
		writer.writeToken( ")" );
	}
}

inline void FaceTexdef_BP_exportTokens( const FaceTexdef& faceTexdef, TokenWriter& writer ){
	// write alternate texdef
	writer.writeToken( "(" );
	{
		writer.writeToken( "(" );
		for ( std::size_t i = 0; i < 3; ++i )
		{
			writer.writeFloat( faceTexdef.m_projection.m_brushprimit_texdef.coords[0][i] );
		}
		writer.writeToken( ")" );
	}
	{
		writer.writeToken( "(" );
		for ( std::size_t i = 0; i < 3; ++i )
		{
			writer.writeFloat( faceTexdef.m_projection.m_brushprimit_texdef.coords[1][i] );
		}
		writer.writeToken( ")" );
	}
	writer.writeToken( ")" );
}

inline void FaceTexdef_exportTokens( const FaceTexdef& faceTexdef, TokenWriter& writer ){
	if( !texdef_sane( faceTexdef.m_projection.m_texdef ) )
		globalWarningStream() << "FaceTexdef_exportTokens: bad texdef\n";
	// write texdef
	writer.writeFloat( faceTexdef.m_projection.m_texdef.shift[0] );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.shift[1] );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.rotate );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.scale[0] );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.scale[1] );
}

inline void FaceTexdef_Valve220_exportTokens( const FaceTexdef& faceTexdef, TokenWriter& writer ){
	if( !texdef_sane( faceTexdef.m_projection.m_texdef ) )
		globalWarningStream() << "FaceTexdef_Valve220_exportTokens: bad texdef\n";
	// write texdef
	writer.writeToken( "[" );
	writer.writeFloat( faceTexdef.m_projection.m_basis_s.x() );
	writer.writeFloat( faceTexdef.m_projection.m_basis_s.y() );
	writer.writeFloat( faceTexdef.m_projection.m_basis_s.z() );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.shift[0] );
	writer.writeToken( "]" );
	writer.writeToken( "[" );
	writer.writeFloat( faceTexdef.m_projection.m_basis_t.x() );
	writer.writeFloat( faceTexdef.m_projection.m_basis_t.y() );
	writer.writeFloat( faceTexdef.m_projection.m_basis_t.z() );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.shift[1] );
	writer.writeToken( "]" );
	writer.writeFloat( -faceTexdef.m_projection.m_texdef.rotate );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.scale[0] );
	writer.writeFloat( faceTexdef.m_projection.m_texdef.scale[1] );
}

inline void FaceShader_ContentsFlagsValue_exportTokens( const FaceShader& faceShader, TokenWriter& writer ){
	// write surface flags
	writer.writeInteger( faceShader.m_flags.m_contentFlags );
	writer.writeInteger( faceShader.m_flags.m_surfaceFlags );
	writer.writeInteger( faceShader.m_flags.m_value );
}

inline void FaceShader_exportTokens( const FaceShader& faceShader, TokenWriter& writer ){
	// write shader name
	if ( string_empty( shader_get_textureName( faceShader.getShader() ) ) ) {
		writer.writeToken( "NULL" );
	}
	else
	{
		writer.writeToken( shader_get_textureName( faceShader.getShader() ) );
	}
}

inline void FaceShader_Doom3_exportTokens( const FaceShader& faceShader, TokenWriter& writer ){
	// write shader name
	if ( string_empty( shader_get_textureName( faceShader.getShader() ) ) ) {
		writer.writeString( "_emptyname" );
	}
	else
	{
		writer.writeString( faceShader.getShader() );
	}
}

class Doom3FaceTokenExporter
{
	const Face& m_face;
public:
	Doom3FaceTokenExporter( const Face& face ) : m_face( face ){
	}
	void exportTokens( TokenWriter& writer ) const {
		FacePlane_Doom3_exportTokens( m_face.getPlane(), writer );
		FaceTexdef_BP_exportTokens( m_face.getTexdef(), writer );
		FaceShader_Doom3_exportTokens( m_face.getShader(), writer );
		FaceShader_ContentsFlagsValue_exportTokens( m_face.getShader(), writer );
		writer.nextLine();
	}
};

class Quake4FaceTokenExporter
{
	const Face& m_face;
public:
	Quake4FaceTokenExporter( const Face& face ) : m_face( face ){
	}
	void exportTokens( TokenWriter& writer ) const {
		FacePlane_Doom3_exportTokens( m_face.getPlane(), writer );
		FaceTexdef_BP_exportTokens( m_face.getTexdef(), writer );
		FaceShader_Doom3_exportTokens( m_face.getShader(), writer );
		writer.nextLine();
	}
};

enum class FaceExportFlags{
	yes,
	no,
	optional
};

template<FaceExportFlags exportFlags>
void FaceFlags_exportTokens( const Face& face, TokenWriter& writer ){
	if constexpr ( exportFlags == FaceExportFlags::yes ){
		FaceShader_ContentsFlagsValue_exportTokens( face.getShader(), writer );
	}
	else if constexpr ( exportFlags == FaceExportFlags::optional ){
		if ( face.getShader().m_flags.m_specified || face.isDetail() ) {
			FaceShader_ContentsFlagsValue_exportTokens( face.getShader(), writer );
		}
	}
}

template<FaceExportFlags exportFlags>
class QuakeFaceTokenExporter
{
	const Face& m_face;
public:
	QuakeFaceTokenExporter( const Face& face ) : m_face( face ){
	}
	void exportTokens( TokenWriter& writer ) const {
		FacePlane_exportTokens( m_face.getPlane(), writer );
		FaceShader_exportTokens( m_face.getShader(), writer );
		FaceTexdef_exportTokens( m_face.getTexdef(), writer );
		FaceFlags_exportTokens<exportFlags>( m_face, writer );
		writer.nextLine();
	}
};

template<typename T>
inline void FaceShader_SiN_AttemptWriteScalar(TokenWriter& writer, const char *key, const T &value, const T &defaultValue)
{
	if (value == defaultValue) {
		return;
	}

	writer.writeToken(key);

	if constexpr(std::is_integral_v<T>) {
		writer.writeInteger(value);
	} else {
		writer.writeFloat(value);
	}
}

inline void FaceShader_SiN_AttemptWriteVector(TokenWriter& writer, const char *key, const Vector3 &value, const Vector3 &defaultValue)
{
	if (value == defaultValue) {
		return;
	}

	writer.writeToken(key);
	writer.writeFloat(value[0]);
	writer.writeFloat(value[1]);
	writer.writeFloat(value[2]);
}

inline void FaceShader_SiN_AttemptWriteString(TokenWriter& writer, const char *key, const CopiedString &value, const CopiedString &defaultValue)
{
	if (value == defaultValue) {
		return;
	}
	
	writer.writeToken(key);
	writer.writeToken(value.c_str());
}

inline void FaceFlags_exportSiNData( const Face& face, TokenWriter& writer ){
	const auto &faceShader = face.getShader();

	// write contents & surface flags
	for (auto &content : sin_contents_names) {
		if (faceShader.m_flags.m_contentFlags & (int) content.flag) {
			std::string s = "+";
			s += content.name;
			writer.writeToken(s.c_str());
		}
	}
	for (auto &surf : sin_surfflag_names) {
		if (faceShader.m_flags.m_surfaceFlags & (int) surf.flag) {
			std::string s = "+";
			s += surf.name;
			writer.writeToken(s.c_str());
		}
	}

	// ugly but whatever
	FaceShader_SiN_AttemptWriteScalar(writer, "animtime", faceShader.m_flags.m_sinData.m_animtime, defaultSiNSurfaceData.m_animtime);
	FaceShader_SiN_AttemptWriteScalar(writer, "friction", faceShader.m_flags.m_sinData.m_friction, defaultSiNSurfaceData.m_friction);
	FaceShader_SiN_AttemptWriteScalar(writer, "restitution", faceShader.m_flags.m_sinData.m_restitution, defaultSiNSurfaceData.m_restitution);
	FaceShader_SiN_AttemptWriteScalar(writer, "direct", faceShader.m_flags.m_sinData.m_direct, defaultSiNSurfaceData.m_direct);
	FaceShader_SiN_AttemptWriteScalar(writer, "directangle", faceShader.m_flags.m_sinData.m_directangle, defaultSiNSurfaceData.m_directangle);
	FaceShader_SiN_AttemptWriteScalar(writer, "translucence", faceShader.m_flags.m_sinData.m_translucence, defaultSiNSurfaceData.m_translucence);
	FaceShader_SiN_AttemptWriteScalar(writer, "trans_mag", faceShader.m_flags.m_sinData.m_trans_mag, defaultSiNSurfaceData.m_trans_mag);
	FaceShader_SiN_AttemptWriteScalar(writer, "trans_angle", faceShader.m_flags.m_sinData.m_trans_angle, defaultSiNSurfaceData.m_trans_angle);
	FaceShader_SiN_AttemptWriteVector(writer, "color", faceShader.m_flags.m_sinData.m_color, defaultSiNSurfaceData.m_color);
	FaceShader_SiN_AttemptWriteScalar(writer, "lightvalue", faceShader.m_flags.m_sinData.m_lightvalue, defaultSiNSurfaceData.m_lightvalue);
	FaceShader_SiN_AttemptWriteScalar(writer, "nonlitvalue", faceShader.m_flags.m_sinData.m_nonlitvalue, defaultSiNSurfaceData.m_nonlitvalue);
	FaceShader_SiN_AttemptWriteString(writer, "directstyle", faceShader.m_flags.m_sinData.m_directstylename, defaultSiNSurfaceData.m_directstylename);
}


template<bool valve220>
class SinFaceTokenExporter
{
	const Face& m_face;
public:
	SinFaceTokenExporter( const Face& face ) : m_face( face ){
	}
	void exportTokens( TokenWriter& writer ) const {
		FacePlane_exportTokens( m_face.getPlane(), writer );
		FaceShader_exportTokens( m_face.getShader(), writer );
		if constexpr(valve220) {
			FaceTexdef_Valve220_exportTokens( m_face.getTexdef(), writer );
		} else {
			FaceTexdef_exportTokens( m_face.getTexdef(), writer );
		}
		FaceFlags_exportSiNData( m_face, writer );
		writer.nextLine();
	}
};

template<FaceExportFlags exportFlags>
class Quake3BPFaceTokenExporter
{
	const Face& m_face;
public:
	Quake3BPFaceTokenExporter( const Face& face ) : m_face( face ){
	}
	void exportTokens( TokenWriter& writer ) const {
		FacePlane_exportTokens( m_face.getPlane(), writer );
		FaceTexdef_BP_exportTokens( m_face.getTexdef(), writer );
		FaceShader_exportTokens( m_face.getShader(), writer );
		FaceFlags_exportTokens<exportFlags>( m_face, writer );
		writer.nextLine();
	}
};

template<FaceExportFlags exportFlags>
class Valve220FaceTokenExporter
{
	const Face& m_face;
public:
	Valve220FaceTokenExporter( const Face& face ) : m_face( face ){
	}
	void exportTokens( TokenWriter& writer ) const {
		FacePlane_exportTokens( m_face.getPlane(), writer );
		FaceShader_exportTokens( m_face.getShader(), writer );
		FaceTexdef_Valve220_exportTokens( m_face.getTexdef(), writer );
		FaceFlags_exportTokens<exportFlags>( m_face, writer );
		writer.nextLine();
	}
};


class BrushTokenImporter : public MapImporter
{
	Brush& m_brush;

public:
	BrushTokenImporter( Brush& brush ) : m_brush( brush ){
	}
	bool importTokens( Tokeniser& tokeniser ) override {
		if ( Brush::m_type == eBrushTypeQuake3BP || Brush::m_type == eBrushTypeQuake2BP || Brush::m_type == eBrushTypeDoom3 || Brush::m_type == eBrushTypeQuake4 ) {
			tokeniser.nextLine();
			RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "{" ) );
		}
		while ( true )
		{
			// check for end of brush
			tokeniser.nextLine();
			const char* token = tokeniser.getToken();
			if ( string_equal( token, "}" ) ) {
				break;
			}

			tokeniser.ungetToken();

			m_brush.push_back( FaceSmartPointer( new Face( &m_brush ) ) );

			//!todo BP support
			tokeniser.nextLine();

			Face& face = *m_brush.back();

			switch ( Brush::m_type )
			{
			case eBrushTypeDoom3:
				{
					Doom3FaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			case eBrushTypeQuake4:
				{
					Quake4FaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			case eBrushTypeQuake:
			case eBrushTypeQuake2:
			case eBrushTypeQuake3:
				{
					QuakeFaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			case eBrushTypeSin:
				{
					SinFaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			case eBrushTypeSinValve220:
				{
					SinValve220FaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			case eBrushTypeQuake2BP:
			case eBrushTypeQuake3BP:
				{
					Quake3BPFaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			case eBrushTypeValve220:
			case eBrushTypeQuake2Valve220:
			case eBrushTypeQuake3Valve220:
				{
					Valve220FaceTokenImporter importer( face );
					RETURN_FALSE_IF_FAIL( importer.importTokens( tokeniser ) );
				}
				break;
			}
			face.planeChanged();
		}
		if ( Brush::m_type == eBrushTypeQuake3BP || Brush::m_type == eBrushTypeQuake2BP || Brush::m_type == eBrushTypeDoom3 || Brush::m_type == eBrushTypeQuake4 ) {
			tokeniser.nextLine();
			RETURN_FALSE_IF_FAIL( Tokeniser_parseToken( tokeniser, "}" ) );
		}

		m_brush.planeChanged();
		m_brush.shaderChanged();

		return true;
	}
};


class BrushTokenExporter : public MapExporter
{
	const Brush& m_brush;

public:
	BrushTokenExporter( const Brush& brush ) : m_brush( brush ){
	}
	void exportTokens( TokenWriter& writer ) const override {
		m_brush.evaluateBRep(); // ensure b-rep is up-to-date, so that non-contributing faces can be identified.

		if ( !m_brush.hasContributingFaces() ) {
			return;
		}

		writer.writeToken( "{" );
		writer.nextLine();

		if ( Brush::m_type == eBrushTypeQuake3BP || Brush::m_type == eBrushTypeQuake2BP ) {
			writer.writeToken( "brushDef" );
			writer.nextLine();
			writer.writeToken( "{" );
			writer.nextLine();
		}
		else if ( Brush::m_type == eBrushTypeDoom3 || Brush::m_type == eBrushTypeQuake4 ) {
			writer.writeToken( "brushDef3" );
			writer.nextLine();
			writer.writeToken( "{" );
			writer.nextLine();
		}

		for ( const auto& face : m_brush )
		{
			if ( face->contributes() ) {
				switch ( Brush::m_type )
				{
				case eBrushTypeDoom3:
					{
						Doom3FaceTokenExporter exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake4:
					{
						Quake4FaceTokenExporter exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake:
					{
						QuakeFaceTokenExporter<FaceExportFlags::no> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake2:
					{
						QuakeFaceTokenExporter<FaceExportFlags::optional> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake3:
					{
						QuakeFaceTokenExporter<FaceExportFlags::yes> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake2BP:
					{
						Quake3BPFaceTokenExporter<FaceExportFlags::optional> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake3BP:
					{
						Quake3BPFaceTokenExporter<FaceExportFlags::yes> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeValve220:
					{
						Valve220FaceTokenExporter<FaceExportFlags::no> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake2Valve220:
					{
						Valve220FaceTokenExporter<FaceExportFlags::optional> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeQuake3Valve220:
					{
						Valve220FaceTokenExporter<FaceExportFlags::yes> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeSin:
					{
						SinFaceTokenExporter<false> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				case eBrushTypeSinValve220:
					{
						SinFaceTokenExporter<true> exporter( *face );
						exporter.exportTokens( writer );
					}
					break;
				}
			}
		}

		if ( Brush::m_type == eBrushTypeQuake3BP || Brush::m_type == eBrushTypeQuake2BP || Brush::m_type == eBrushTypeDoom3 || Brush::m_type == eBrushTypeQuake4 ) {
			writer.writeToken( "}" );
			writer.nextLine();
		}

		writer.writeToken( "}" );
		writer.nextLine();
	}
};
