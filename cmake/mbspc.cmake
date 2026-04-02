
# mbspc

find_package(Math)

add_executable(mbspc
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/be_aas_bspq3.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/be_aas_cluster.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/be_aas_move.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/be_aas_optimize.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/be_aas_reach.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/be_aas_sample.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/l_libvar.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/l_precomp.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/l_script.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/botlib/l_struct.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_areamerging.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_cfg.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_create.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_edgemelting.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_facemerging.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_file.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_gsubdiv.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_map.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_prunenodes.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/aas_store.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/be_aas_bspc.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/brushbsp.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/bspc.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/csg.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/faces.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/glfile.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_bsp_ent.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_bsp_hl.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_bsp_q1.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_bsp_q2.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_bsp_q3.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_bsp_sin.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_cmd.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_log.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_math.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_mem.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_poly.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_qfiles.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_threads.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/l_utils.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/leakfile.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/map.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/map_hl.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/map_q1.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/map_q2.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/map_q3.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/map_sin.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/nodraw.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/portals.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/prtfile.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/textures.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/tree.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/mbspc/writebsp.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/qcommon/cm_load.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/qcommon/cm_patch.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/qcommon/cm_test.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/qcommon/cm_trace.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/qcommon/md4.c
	${PROJECT_SOURCE_DIR}/tools/mbspc/qcommon/unzip.c
)
target_link_libraries(mbspc PRIVATE $<TARGET_NAME_IF_EXISTS:Math::Math>)
target_include_directories(mbspc PRIVATE
	${PROJECT_SOURCE_DIR}/libs
	${PROJECT_SOURCE_DIR}/tools/mbspc
)
target_compile_definitions(mbspc PRIVATE
	RADIANT_VERSION=\"${RADIANT_VERSION}\"
	RADIANT_MAJOR_VERSION=\"${RADIANT_MAJOR_VERSION}\"
	RADIANT_MINOR_VERSION=\"${RADIANT_MINOR_VERSION}\"
	RADIANT_ABOUTMSG=\"${RADIANT_ABOUTMSG}\"
	BSPC
	BSPCINCLUDE
)
set_target_properties(mbspc
	PROPERTIES
		CXX_STANDARD_REQUIRED ON
		CXX_STANDARD 20
		LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/install
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/install
)
if(DEFINED CMAKE_SYSTEM_PROCESSOR)
	string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} SYSTEM_PROCESSOR)
	set_target_properties(mbspc PROPERTIES SUFFIX ".${SYSTEM_PROCESSOR}")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(mbspc PRIVATE WIN32)
else()
	target_compile_definitions(mbspc PRIVATE POSIX XWINDOWS)
endif()
