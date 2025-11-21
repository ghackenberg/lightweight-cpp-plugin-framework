add_library(Plugins_DummyApplication SHARED
	"Build.h"
	"Namespace.h"
	"main.cpp"
	"Service.h"
	"Service.cpp"
	"Application.h"
	"Application.cpp")

target_link_libraries(Plugins_DummyApplication Core)

configure_file("Plugin.xml" "Plugin.xml")