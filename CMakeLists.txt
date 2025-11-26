# CMake

cmake_minimum_required(VERSION 4.1)

project(lightweight-cpp-plugin-framework
	VERSION 0.1.0
	DESCRIPTION "A lightweight C++ plugin framework"
	HOMEPAGE_URL "https://github.com/ghackenberg/lightweight-cpp-plugin-framework"
	LANGUAGES CXX)

set(CMAKE_DEBUG_POSTFIX "_d")

# C++

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Boost

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS property_tree REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})

# SDL3

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

include_directories(${SDL3_INCLUDE_DIRS})

# Self

include_directories("${CMAKE_SOURCE_DIR}/Sources")

# Core

add_library(Core SHARED
	"Sources/Core/Platform.h"
	"Sources/Core/Build.h"
	"Sources/Core/Registry.h"
	"Sources/Core/Registry.cpp"
	"Sources/Core/Plugin.h"
	"Sources/Core/Plugin.cpp"
	"Sources/Core/Service.h"
	"Sources/Core/Service.cpp"
	"Sources/Core/Application.h"
	"Sources/Core/Application.cpp"
	"Sources/Core/Library.h"
	"Sources/Core/Library.cpp"
	"Sources/Core/Factory.h"
	"Sources/Core/Factory.cpp")

configure_file("Sources/Core/ExtensionMap.bat" "ExtensionMap.bat")

# Main

add_executable(Main
	"Sources/Main/main.cpp")

target_link_libraries(Main Core)

if (EXISTS "Sources/Main/Configuration.xml")
	configure_file("Sources/Main/Configuration.xml" "Configuration.xml")
else()
	configure_file("Sources/Main/Configuration.default.xml" "Configuration.xml")
endif()

# Plugins

## DummyApplicationCli

add_library(PluginDummyApplicationCli SHARED
	"Sources/Plugins/DummyApplicationCli/Build.h"
	"Sources/Plugins/DummyApplicationCli/main.cpp"
	"Sources/Plugins/DummyApplicationCli/Service.h"
	"Sources/Plugins/DummyApplicationCli/Service.cpp"
	"Sources/Plugins/DummyApplicationCli/Application.h"
	"Sources/Plugins/DummyApplicationCli/Application.cpp")

target_link_libraries(PluginDummyApplicationCli Core)

configure_file("Sources/Plugins/DummyApplicationCli/Plugin.xml" "PluginDummyApplicationCli.xml")

## DummyApplicationGui

add_library(PluginDummyApplicationGui SHARED
	"Sources/Plugins/DummyApplicationGui/Build.h"
	"Sources/Plugins/DummyApplicationGui/main.cpp"
	"Sources/Plugins/DummyApplicationGui/Application.h"
	"Sources/Plugins/DummyApplicationGui/Application.cpp")

target_link_libraries(PluginDummyApplicationGui Core)
target_link_libraries(PluginDummyApplicationGui SDL3::SDL3)

configure_file("Sources/Plugins/DummyApplicationGui/Plugin.xml" "PluginDummyApplicationGui.xml")

## DummyService

add_library(PluginDummyService SHARED
	"Sources/Plugins/DummyService/Build.h"
	"Sources/Plugins/DummyService/main.cpp"
	"Sources/Plugins/DummyService/Service.h"
	"Sources/Plugins/DummyService/Service.cpp")

target_link_libraries(PluginDummyService Core)
target_link_libraries(PluginDummyService PluginDummyApplicationCli)

configure_file("Sources/Plugins/DummyService/Plugin.xml" "PluginDummyService.xml")