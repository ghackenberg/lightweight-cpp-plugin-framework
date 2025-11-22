find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

include_directories(${SDL3_INCLUDE_DIRS})

add_library(Plugins_DummyApplicationGui SHARED
	"Build.h"
	"main.cpp"
	"Application.h"
	"Application.cpp")

target_link_libraries(Plugins_DummyApplicationGui Core)
target_link_libraries(Plugins_DummyApplicationGui SDL3::SDL3)

configure_file("Plugin.xml" "Plugin.xml")