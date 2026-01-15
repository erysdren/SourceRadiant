
# ddslib

add_library(ddslib STATIC
	${PROJECT_SOURCE_DIR}/libs/ddslib/ddslib.c
)

target_include_directories(ddslib PRIVATE
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/libs
)

# etclib

add_library(etclib STATIC
	${PROJECT_SOURCE_DIR}/libs/etclib.c
)

target_include_directories(etclib PRIVATE
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/libs
)

# q3map2

add_executable(q3map2
	${PROJECT_SOURCE_DIR}/tools/quake3/common/cmdlib.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/qimagelib.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/inout.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/jpeg.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/md4.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/mutex.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/polylib.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/scriplib.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/threads.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/unzip.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/vfs.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/common/miniz.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/autopk3.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/brush.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/bspfile_abstract.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/bspfile_ibsp.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/bspfile_rbsp.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/bsp.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/convert_ase.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/convert_bsp.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/convert_json.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/convert_map.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/convert_obj.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/decals.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/exportents.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/facebsp.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/fog.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/games.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/help.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/image.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/leakfile.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/light_bounce.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/lightmaps_ydnar.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/light.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/light_trace.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/light_ydnar.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/main.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/map.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/minimap.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/mesh.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/model.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/patch.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/path_init.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/portals.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/prtfile.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/shaders.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/surface_extra.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/surface_foliage.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/surface_fur.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/surface_meta.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/surface.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/tjunction.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/tree.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/visflow.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/vis.cpp
	${PROJECT_SOURCE_DIR}/tools/quake3/q3map2/writebsp.cpp
)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(q3map2 PRIVATE -MMD -W -Wall -Wcast-align -Wcast-qual -Wno-unused-parameter -Wno-unused-function -fno-strict-aliasing)
	target_compile_options(q3map2 PRIVATE -Wreorder -fno-exceptions -fno-rtti)
endif()
target_link_libraries(q3map2 PRIVATE l_net filematch ddslib etclib)
target_link_libraries(q3map2 PRIVATE LibXml2::LibXml2)
target_link_libraries(q3map2 PRIVATE assimp)
target_link_libraries(q3map2 PRIVATE PNG::PNG $<TARGET_NAME_IF_EXISTS:JPEG::JPEG>)
target_include_directories(q3map2 PRIVATE
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/libs
	${PROJECT_SOURCE_DIR}/tools/quake3/common
)
target_compile_definitions(q3map2 PRIVATE
	RADIANT_VERSION=\"${RADIANT_VERSION}\"
	RADIANT_MAJOR_VERSION=\"${RADIANT_MAJOR_VERSION}\"
	RADIANT_MINOR_VERSION=\"${RADIANT_MINOR_VERSION}\"
	RADIANT_ABOUTMSG=\"${RADIANT_ABOUTMSG}\"
	Q3MAP_VERSION=\"${Q3MAP_VERSION}\"
	$<IF:$<TARGET_EXISTS:JPEG::JPEG>,,NO_JPEG>
	NO_WEBP
	NO_CRN
)
set_target_properties(q3map2
	PROPERTIES
		CXX_STANDARD_REQUIRED ON
		CXX_STANDARD 20
		LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/install
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/install
)
if(DEFINED CMAKE_SYSTEM_PROCESSOR)
	string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} SYSTEM_PROCESSOR)
	set_target_properties(q3map2 PROPERTIES SUFFIX ".${SYSTEM_PROCESSOR}")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(q3map2 PRIVATE WIN32)
else()
	target_compile_definitions(q3map2 PRIVATE POSIX XWINDOWS)
endif()
