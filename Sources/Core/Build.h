#pragma once

#include "Platform.h"

#ifdef Core_EXPORTS
#	define CORE_API CORE_EXPORT
#else
#	define CORE_API CORE_IMPORT
#endif