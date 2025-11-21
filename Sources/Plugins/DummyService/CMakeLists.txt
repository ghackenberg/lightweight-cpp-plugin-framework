add_library(Plugins_DummyService SHARED
	Build.h
	main.cpp
	Service.h
	Service.cpp)

target_link_libraries(Plugins_DummyService Core)
target_link_libraries(Plugins_DummyService Plugins_DummyApplicationCli)

configure_file(Plugin.xml Plugin.xml)