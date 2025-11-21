#ifndef CORE_LIBRARY_H
#define CORE_LIBRARY_H

#include "Build.h"
#include <string>
#include <boost/shared_ptr.hpp>
#
#ifdef CORE_WINDOWS
#	include "Windows.h"
#	define LIBRARY_HANDLE HMODULE
#	define LIBRARY_LOAD(name) LoadLibrary(name)
#	define LIBRARY_UNLOAD(handle) FreeLibrary(handle)
#	define LIBRARY_SYMBOL(handle, name) GetProcAddress(handle, name)
#	define LIBRARY_EXTENSION "dll"
#else
#	error "Platform not defined!"
#endif

namespace Core
{
	
	/// Cross platform shared library wrapper.
	class CORE_API Library
	{
	public:

		/// Create the library with the given filename.
		Library(const std::string &filename);
		/// Unload the library if it was loaded.
		~Library();

		/// Load the library.
		void load();
		/// Unload the library.
		void unload();

		/// Retrieve a symbol pointer from the library.
		void* getSymbol(const std::string &name);

	private:

		/// The loaded flag.
		bool mLoaded;
		/// The file name of the library.
		std::string mFilename;

		/// The operating system handle.
		LIBRARY_HANDLE mHandle;
	};

	/// Shared library object.
	typedef boost::shared_ptr<Library> LibraryPtr;

}

#endif