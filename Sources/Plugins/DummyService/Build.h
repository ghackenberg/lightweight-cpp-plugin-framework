#pragma once

#include <Core/Platform.h>

#ifdef PluginDummyService_EXPORTS
#	define PLUGIN_DUMMY_SERVICE_API CORE_EXPORT
#else
#	define PLUGIN_DUMMY_SERVICE_API CORE_IMPORT
#endif