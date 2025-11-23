#pragma once

#include <Core/Platform.h>

#ifdef PluginDummyApplicationGui_EXPORTS
#	define PLUGIN_DUMMY_APPLICATION_GUI_API CORE_EXPORT
#else
#	define PLUGIN_DUMMY_APPLICATION_GUI_API CORE_IMPORT
#endif