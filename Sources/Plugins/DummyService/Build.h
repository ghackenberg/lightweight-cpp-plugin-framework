#pragma once

#include <Core/Platform.h>

#ifdef Plugins_DummyService_EXPORTS
#	define PLUGINS_DUMMYSERVICE_API CORE_EXPORT
#else
#	define PLUGINS_DUMMYSERVICE_API CORE_IMPORT
#endif