#pragma once

#include <Core/Platform.h>

#ifdef PluginDummyApplicationCli_EXPORTS
#	define PLUGIN_DUMMY_APPLICATION_CLI_API CORE_EXPORT
#else
#	define PLUGIN_DUMMY_APPLICATION_CLI_API CORE_IMPORT
#endif