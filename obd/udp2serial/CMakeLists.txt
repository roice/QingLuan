#====================================================
# CMakeLists configuration file for GPS Emulator
# 
# Author: Roice(LUO Bing)
# Date:   
#         2017-06-16 Create this file
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

#====================================================
# ================ User can Access ==================
#====================================================
# Project name
set(PRJ_NAME udp2serial)
# Debug version
set(CMAKE_BUILD_TYPE Debug)
# ===================================================

#====================================================
# ============= Don't touch the following ===========
#====================================================
project(${PRJ_NAME})
#======== Detect which platform in use ========
# if compile on Mac OSX, the "-framework Cocoa" flag should be added
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework GLUT")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework GLUT")
    message("Compile on APPLE MACOSX")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    message("Compile on UNIX")
endif()

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#============== Find Dependencies ================
#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#============== Build the project ================
#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#---- source files include path settings ----
# add source directory into include path
#   add root dir to search for header files of GSRAO projects
include_directories(${PROJECT_SOURCE_DIR}/src)

#---- library files path settings ----
# add library dir into lib path

#---- start compiling ----
# compile main file
add_executable(${PRJ_NAME} src/main.cxx src/config.cxx
    src/udp_receive.cxx src/thread_comm.cxx
    )
    
target_compile_features(${PRJ_NAME} PRIVATE cxx_constexpr)

#---- start linking ----
# Note: the former line depends on the next line
target_link_libraries(${PRJ_NAME} pthread)
