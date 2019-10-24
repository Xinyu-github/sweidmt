# Written by Christoph Hänisch
# Copyright 2015-2016 Chair of Medical Engineering (mediTEC), RWTH Aachen University
# License: BSD License
# Version 1.0
# Last changed on 2016-04-06

cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_DEBUG_POSTFIX d)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)


########################################################################################
# Project name
########################################################################################

project(MyApp)


########################################################################################
# Version declaration (target file will be named with version suffix)
########################################################################################

set(MAJOR_VERSION        1)
set(MINOR_VERSION        0)
set(PATCH_LEVEL          0)

set(FULL_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_LEVEL})

set(TARGET_NAME ${PROJECT_NAME}-${FULL_VERSION})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/misc/run.bat.in ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}.bat @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/doc/Doxyfile.in ${CMAKE_CURRENT_SOURCE_DIR}/src/doc/Doxyfile @ONLY)


########################################################################################
# Global definitions (pre-processor)
########################################################################################

add_definitions(-DNOMINMAX)
add_definitions(-DSWEIDMT_DLL_EXPORTS)


########################################################################################
# Compiler settings
########################################################################################

# OpenMP

include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


########################################################################################
# Qt 5 setting
########################################################################################

# References: http://doc.qt.io/qt-5/cmake-manual.html

message("-- Check for Qt5 (Note: On Windows the Qt binary folder must be set in the PATH environment variable)")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc, uic, and rcc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the Qt libraries
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

message("-- Check for Qt5 - Success")


########################################################################################
# Other dependencies
########################################################################################

# QFrameworkDLL

set(QFrameworkDLL_INCLUDE ${CMAKE_PROJECT_DIR}libs/QFrameworkDLL/1.0.0/include)
set(QFrameworkDLL_LIBDIR ${CMAKE_PROJECT_DIR}libs/QFrameworkDLL/1.0.0/bin)
set(QFrameworkDLL_LIBLIST
    optimized QFrameworkDLL_msvc2015_win32_1.0.0
    debug QFrameworkDLL_msvc2015_win32_1.0.0d
)
link_directories(${QFrameworkDLL_LIBDIR})


########################################################################################
# Source, header, form, and resource files
########################################################################################

include_directories(${CMAKE_PROJECT_DIR}src
                    ${CMAKE_CURRENT_BINARY_DIR}
					${QFrameworkDLL_INCLUDE}
)

set(HEADERS
	src/ApplicationData.h
	src/QFrameworkApplication.h
	src/TestWidget1.h
	src/TestWidget3.h
)

set(SRC
	src/ApplicationData.cpp
	src/QFrameworkApplication.cpp
	src/TestWidget1.cpp
	src/TestWidget3.cpp
)

set(FORMS
	src/TestWidget1.ui
	src/TestWidget3.ui
)

set(RESOURCES
)

set(DLL_HEADERS
    src/dll.hpp
)

set(DLL_SRC
    src/dll.cpp
)



########################################################################################
# Define executable(s) and libraries (e.g. DLLs)
########################################################################################

link_directories(${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(${TARGET_NAME} WIN32
               ${SRC}
               ${HEADERS}
               ${FORMS}
               ${RESOURCES}
)

add_library(SWEIDMT_DLL SHARED ${DLL_HEADERS} ${DLL_SRC})

target_link_libraries(SWEIDMT_DLL
	${QFrameworkDLL_LIBLIST}
)
## set TARGET_NAME as start project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})


########################################################################################
# Add dependencies to the linker
########################################################################################

target_link_libraries(${TARGET_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
	${QFrameworkDLL_LIBLIST}
    SWEIDMT_DLL
)

#########################################################################################
# Copy all necessary .dll files to the output directories
#########################################################################################

string(REPLACE / \\ bin_debug_path ${PROJECT_BINARY_DIR}\\bin\\Debug)
string(REPLACE / \\ bin_release_path ${PROJECT_BINARY_DIR}\\bin\\Release)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${bin_debug_path})
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${bin_release_path})

string(REPLACE / \\ src_data_path "${PROJECT_SOURCE_DIR}\\libs\\QFrameworkDLL\\1.0.0\\bin\\QFrameworkDLL_msvc2015_win32_1.0.0d.dll")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND echo Update: ${src_data_path})
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND xcopy /d /y /s /i ${src_data_path} ${bin_debug_path})
string(REPLACE / \\ src_data_path "${PROJECT_SOURCE_DIR}\\libs\\QFrameworkDLL\\1.0.0\\bin\\QFrameworkDLL_msvc2015_win32_1.0.0.dll")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND echo Update: ${src_data_path})
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND xcopy /d /y /s /i ${src_data_path} ${bin_release_path})


########################################################################################
# Visual Studio specific settings
########################################################################################

if(MSVC)
    # Object Level Parallelism (parallel builds)
    add_definitions(/MP)

    # Open console window on debug builds.
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif()


############################################################################################
#                       NO CHANGES EVER NECESSARY BELOW THIS POINT!!                       #
############################################################################################

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/debug CONFIGURATIONS Debug
)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/release CONFIGURATIONS Release
)
