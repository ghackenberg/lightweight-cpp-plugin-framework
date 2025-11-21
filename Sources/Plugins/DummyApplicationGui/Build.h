#pragma once

#include <Core/Platform.h>

#ifdef Plugins_DummyApplicationGui_EXPORTS
#	define PLUGINS_DUMMYAPPLICATIONGUI_API CORE_EXPORT
#else
#	define PLUGINS_DUMMYAPPLICATIONGUI_API CORE_IMPORT
#endif