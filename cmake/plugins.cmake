# plugins are generally optional and extend editor functionality

function(add_plugin name)
	cmake_parse_arguments(PARSE_ARGV 1 ARG "" "" "SOURCES")
	add_library(${name} SHARED ${ARG_SOURCES})
	set_target_properties(${name}
		PROPERTIES
			CXX_STANDARD_REQUIRED ON
			CXX_STANDARD 20
			LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/install/plugins
			RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/install/plugins
			PREFIX ""
	)
	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		target_compile_definitions(${name} PRIVATE WIN32)
	else()
		target_compile_definitions(${name} PRIVATE POSIX XWINDOWS)
	endif()
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${name} PRIVATE -MMD -W -Wall -Wcast-align -Wcast-qual -Wno-unused-parameter -Wno-unused-function -fno-strict-aliasing)
		target_compile_options(${name} PRIVATE -Wreorder -fno-exceptions -fno-rtti)
	endif()
	target_include_directories(${name} PRIVATE
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/libs
	)
	target_compile_definitions(${name} PRIVATE QT_NO_KEYWORDS)
	target_compile_definitions(${name} PRIVATE
		RADIANT_VERSION=\"${RADIANT_VERSION}\"
		RADIANT_MAJOR_VERSION=\"${RADIANT_MAJOR_VERSION}\"
		RADIANT_MINOR_VERSION=\"${RADIANT_MINOR_VERSION}\"
		RADIANT_ABOUTMSG=\"${RADIANT_ABOUTMSG}\"
	)
endfunction()

add_plugin(brushexport
	SOURCES
		${PROJECT_SOURCE_DIR}/plugins/brushexport/callbacks.cpp
		${PROJECT_SOURCE_DIR}/plugins/brushexport/export.cpp
		${PROJECT_SOURCE_DIR}/plugins/brushexport/interface.cpp
		${PROJECT_SOURCE_DIR}/plugins/brushexport/plugin.cpp
)
target_link_libraries(brushexport PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::OpenGL Qt6::OpenGLWidgets)

add_plugin(prtview
	SOURCES
		${PROJECT_SOURCE_DIR}/plugins/prtview/AboutDialog.cpp
		${PROJECT_SOURCE_DIR}/plugins/prtview/ConfigDialog.cpp
		${PROJECT_SOURCE_DIR}/plugins/prtview/LoadPortalFileDialog.cpp
		${PROJECT_SOURCE_DIR}/plugins/prtview/portals.cpp
		${PROJECT_SOURCE_DIR}/plugins/prtview/prtview.cpp
)
target_link_libraries(prtview PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::OpenGL Qt6::OpenGLWidgets)

add_plugin(sunplug
	SOURCES
		${PROJECT_SOURCE_DIR}/plugins/sunplug/sunplug.cpp
)
target_link_libraries(sunplug PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::OpenGL Qt6::OpenGLWidgets)

add_plugin(ufoaiplug
	SOURCES
		${PROJECT_SOURCE_DIR}/plugins/ufoaiplug/ufoai_filters.cpp
		${PROJECT_SOURCE_DIR}/plugins/ufoaiplug/ufoai_gtk.cpp
		${PROJECT_SOURCE_DIR}/plugins/ufoaiplug/ufoai_level.cpp
		${PROJECT_SOURCE_DIR}/plugins/ufoaiplug/ufoai.cpp
)
target_link_libraries(ufoaiplug PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::OpenGL Qt6::OpenGLWidgets)

add_plugin(meshtex
	SOURCES
		${PROJECT_SOURCE_DIR}/plugins/meshtex/GeneralFunctionDialog.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/GenericDialog.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/GenericMainMenu.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/GenericPluginUI.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/GetInfoDialog.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/MainMenu.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/MeshEntity.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/MeshVisitor.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/PluginModule.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/PluginRegistration.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/PluginUI.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/RefCounted.cpp
		${PROJECT_SOURCE_DIR}/plugins/meshtex/SetScaleDialog.cpp
)
target_link_libraries(meshtex PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::OpenGL Qt6::OpenGLWidgets)
