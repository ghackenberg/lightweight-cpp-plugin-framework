add_library(Plugins_DummyApplicationGui SHARED
	"Build.h"
	"main.cpp"
	"Application.h"
	"Application.cpp")

target_link_libraries(Plugins_DummyApplicationGui Core)

configure_file("Plugin.xml" "Plugin.xml")