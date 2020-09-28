cmake_minimum_required(VERSION 2.8)

project(basicLocator)

include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

set(PROJECT_NAME basicLocator)
set(OpenGL_PATH /System/Library/Frameworks/OpenGL.framework)

set(SOURCE_FILES
    basicLocator.h
    basicLocator.cpp
    basicLocatorOverride.h
    basicLocatorOverride.cpp
    mainPlugin.cpp

)

set(LIBRARIES
    OpenMaya
    Foundation
    OpenMayaUI
    OpenMayaAnim
    OpenMayaRender
    OpenGL
)

build_plugin()
