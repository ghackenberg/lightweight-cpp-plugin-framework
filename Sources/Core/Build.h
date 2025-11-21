#ifndef CORE_BUILD_H
#define CORE_BUILD_H

#include "Platform.h"

#ifdef Core_EXPORTS
#	define CORE_API CORE_EXPORT
#else
#	define CORE_API CORE_IMPORT
#endif

#endif