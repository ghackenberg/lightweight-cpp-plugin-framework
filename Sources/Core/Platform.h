#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#ifdef WIN32
#	define CORE_WINDOWS
#else
#	warning "Platform is not supported!"
#endif

#if defined(CORE_WINDOWS)
#	define CORE_EXPORT __declspec(dllexport)
#	define CORE_IMPORT __declspec(dllimport)
#	define CORE_EXTERN extern "C"
#	pragma warning (disable: 4251)
#else
#	define CORE_EXPORT
#	define CORE_IMPORT
#	define CORE_EXTERN
#endif

#endif