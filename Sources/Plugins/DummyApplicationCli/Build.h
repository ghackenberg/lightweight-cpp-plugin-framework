#pragma once

#include <Core/Platform.h>

#ifdef Plugins_DummyApplicationCli_EXPORTS
#	define PLUGINS_DUMMYAPPLICATIONCLI_API CORE_EXPORT
#else
#	define PLUGINS_DUMMYAPPLICATIONCLI_API CORE_IMPORT
#endif