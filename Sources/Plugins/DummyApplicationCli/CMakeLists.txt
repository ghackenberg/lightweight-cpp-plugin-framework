add_library(Plugins_DummyApplicationCli SHARED
	"Build.h"
	"main.cpp"
	"Service.h"
	"Service.cpp"
	"Application.h"
	"Application.cpp")

target_link_libraries(Plugins_DummyApplicationCli Core)

configure_file("Plugin.xml" "Plugin.xml")