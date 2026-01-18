
function(add_gamepack name)
	cmake_parse_arguments(PARSE_ARGV 1 ARG "HAS_BASEGAME;USE_NEW_OUTPUT_SEPARATOR;GOLDSRC" "ENTITIES;PREFIX;BASE_TITLE;BASE_GAMEDIR;TITLE;GAMEDIR;PATH_WIN32;PATH_LINUX;PATH_MACOS;EXECUTABLE_WIN32;EXECUTABLE_LINUX;EXECUTABLE_MACOS" "KNOWN_TITLES;KNOWN_GAMEDIRS")
	file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/install/gamepacks/games/")
	file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/")
	if(ARG_GOLDSRC)
		file(COPY "${PROJECT_SOURCE_DIR}/cmake/default_build_menu_goldsrc_ericwtools.xml" DESTINATION "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/")
		file(RENAME "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/default_build_menu_goldsrc_ericwtools.xml" "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/default_build_menu.xml")
	else()
		file(COPY "${PROJECT_SOURCE_DIR}/cmake/default_build_menu_source.xml" DESTINATION "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/")
		file(RENAME "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/default_build_menu_source.xml" "${PROJECT_SOURCE_DIR}/install/gamepacks/${name}.game/default_build_menu.xml")
	endif()
	set(target gamepack_${name})
	add_custom_target(${target})
	if(ARG_HAS_BASEGAME)
		set_property(TARGET ${target} PROPERTY HAS_BASEGAME 1)
		set_property(TARGET ${target} PROPERTY BASE_GAMEDIR ${ARG_BASE_GAMEDIR})
		set_property(TARGET ${target} PROPERTY BASE_TITLE ${ARG_BASE_TITLE})
		set_property(TARGET ${target} PROPERTY KNOWN_GAMEDIRS ${ARG_KNOWN_GAMEDIRS})
		set_property(TARGET ${target} PROPERTY KNOWN_TITLES ${ARG_KNOWN_TITLES})
	else()
		set_property(TARGET ${target} PROPERTY HAS_BASEGAME 0)
	endif()
	if(ARG_USE_NEW_OUTPUT_SEPARATOR)
		set_property(TARGET ${target} PROPERTY USE_NEW_OUTPUT_SEPARATOR 1)
	else()
		set_property(TARGET ${target} PROPERTY USE_NEW_OUTPUT_SEPARATOR 0)
	endif()
	if(ARG_GOLDSRC)
		set_property(TARGET ${target} PROPERTY GOLDSRC 1)
	else()
		set_property(TARGET ${target} PROPERTY GOLDSRC 0)
	endif()
	set_property(TARGET ${target} PROPERTY PREFIX ${ARG_PREFIX})
	set_property(TARGET ${target} PROPERTY PATH_WIN32 ${ARG_PATH_WIN32})
	set_property(TARGET ${target} PROPERTY PATH_LINUX ${ARG_PATH_LINUX})
	set_property(TARGET ${target} PROPERTY PATH_MACOS ${ARG_PATH_MACOS})
	set_property(TARGET ${target} PROPERTY EXECUTABLE_WIN32 ${ARG_EXECUTABLE_WIN32})
	set_property(TARGET ${target} PROPERTY EXECUTABLE_LINUX ${ARG_EXECUTABLE_LINUX})
	set_property(TARGET ${target} PROPERTY EXECUTABLE_MACOS ${ARG_EXECUTABLE_MACOS})
	set_property(TARGET ${target} PROPERTY ENTITIES ${ARG_ENTITIES})
	set_property(TARGET ${target} PROPERTY GAMEDIR ${ARG_GAMEDIR})
	set_property(TARGET ${target} PROPERTY TITLE ${ARG_TITLE})
	file(GENERATE
		OUTPUT "${PROJECT_SOURCE_DIR}/install/gamepacks/games/${name}.game"
		CONTENT
[[<?xml version="1.0"?>
<game
  type="$<IF:$<TARGET_PROPERTY:GOLDSRC>,hl,source>"
  index="1"
  name="$<TARGET_PROPERTY:TITLE>"
  enginepath_win32="$<TARGET_PROPERTY:PATH_WIN32>"
  enginepath_linux="$<TARGET_PROPERTY:PATH_LINUX>"
  enginepath_macos="$<TARGET_PROPERTY:PATH_MACOS>"
  engine_win32="$<TARGET_PROPERTY:EXECUTABLE_WIN32>"
  engine_linux="$<TARGET_PROPERTY:EXECUTABLE_LINUX>"
  engine_macos="$<TARGET_PROPERTY:EXECUTABLE_MACOS>"
  prefix="$<TARGET_PROPERTY:PREFIX>"
  basegame="$<IF:$<TARGET_PROPERTY:HAS_BASEGAME>,$<TARGET_PROPERTY:BASE_GAMEDIR>,$<TARGET_PROPERTY:GAMEDIR>>"
  basegamename="$<IF:$<TARGET_PROPERTY:HAS_BASEGAME>,$<TARGET_PROPERTY:BASE_TITLE>,$<TARGET_PROPERTY:TITLE>>"
  knowngames="$<LIST:JOIN,$<TARGET_PROPERTY:KNOWN_GAMEDIRS>, >"
  knowngamenames="$<LIST:JOIN,$<TARGET_PROPERTY:KNOWN_TITLES>,$<SEMICOLON>>"
  shaderpath="$<IF:$<TARGET_PROPERTY:GOLDSRC>,textures,materials>"
  archivetypes="$<IF:$<TARGET_PROPERTY:GOLDSRC>,pak wad,vpk gma gcf>"
  texturetypes="$<IF:$<TARGET_PROPERTY:GOLDSRC>,hlw spr mdl,vtf tth>"
  modeltypes="mdl"
  soundtypes="$<IF:$<TARGET_PROPERTY:GOLDSRC>,wav,wav mp3>"
  maptypes="$<IF:$<TARGET_PROPERTY:GOLDSRC>,maphl,mapvmf>"
  shaders="$<IF:$<TARGET_PROPERTY:GOLDSRC>,quake3,source>"
  entityclass="quake3"
  entityclasstype="fgd"
  entities="source"
  entitiesfilename="$<TARGET_PROPERTY:ENTITIES>"
  brushtypes="halflife"
  patchtypes="quake3"
  default_scale="$<IF:$<TARGET_PROPERTY:GOLDSRC>,1.0,0.25>"
  no_patch="1"
  no_plugins="0"
  no_bsp_monitor="1"
  no_autocaulk="1"
  no_outputs="$<IF:$<TARGET_PROPERTY:GOLDSRC>,1,0>"
  show_wads="$<IF:$<TARGET_PROPERTY:GOLDSRC>,1,0>"
  mapextension="$<IF:$<TARGET_PROPERTY:GOLDSRC>,.map,.vmf>"
  mapbackupextension="$<IF:$<TARGET_PROPERTY:GOLDSRC>,.bak,.vmx>"
  use_new_output_separator="$<TARGET_PROPERTY:USE_NEW_OUTPUT_SEPARATOR>"
  shader_caulk = "materials/tools/toolsskip"
  shader_trigger = "materials/tools/toolstrigger"
  shader_clip = "materials/tools/toolsclip"
  shader_nodraw = "materials/tools/toolsnodraw"
  shader_hint = "materials/tools/toolshint"
/>
]]
	TARGET ${target}
	)
endfunction()

# source engine gamepacks
include(gamepacks/source)

# goldsrc engine gamepacks
include(gamepacks/goldsrc)

# put your custom gamepacks in here:
# cmake/gamepacks/user.cmake
include(gamepacks/user OPTIONAL)
