#pragma once

#include <Core/Platform.h>

#ifdef Plugins_DummyApplication_EXPORTS
#	define PLUGINS_DUMMYAPPLICATION_API CORE_EXPORT
#else
#	define PLUGINS_DUMMYAPPLICATION_API CORE_IMPORT
#endif