# CMake

cmake_minimum_required(VERSION 4.1)

project(lightweight-cpp-plugin-framework
	VERSION 0.1.0
	DESCRIPTION "A lightweight C++ plugin framework"
	HOMEPAGE_URL "https://github.com/ghackenberg/lightweight-cpp-plugin-framework"
	LANGUAGES CXX)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Boost

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS property_tree REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})

# Self

include_directories(${CMAKE_SOURCE_DIR}/Sources)

# Framework Core Library

add_library(Core SHARED
	Sources/Core/Platform.h
	Sources/Core/Build.h
	Sources/Core/Namespace.h
	Sources/Core/Registry.h
	Sources/Core/Registry.cpp
	Sources/Core/Plugin.h
	Sources/Core/Plugin.cpp
	Sources/Core/Service.h
	Sources/Core/Service.cpp
	Sources/Core/Application.h
	Sources/Core/Application.cpp
	Sources/Core/Library.h
	Sources/Core/Library.cpp
	Sources/Core/Factory.h
	Sources/Core/Factory.cpp
	Sources/Core/ExtensionMap.bat)

# Framework Main Executable

add_executable(Main
	Sources/Main/main.cpp)

target_link_libraries(Main Core)

configure_file(Sources/Main/Configuration.xml Configuration.xml)

# Plugins

add_subdirectory(Sources/Plugins Plugins)