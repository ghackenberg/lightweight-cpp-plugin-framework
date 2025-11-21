#include "Library.h"
#include <cassert>

#ifndef _NDEBUG
#	define LIBRARY_SUFFIX "_d"
#else
#	define LIBRARY_SUFFIX ""
#endif

using namespace Core;

Library::Library(const std::string &filename) : mLoaded(false), mFilename(filename)
{
	mFilename.append(LIBRARY_SUFFIX).append(".").append(LIBRARY_EXTENSION);
}
Library::~Library()
{
	if (mLoaded)
		unload();
}

void Library::load()
{
	assert(!mLoaded);
	mHandle = LIBRARY_LOAD(mFilename.c_str());
	mLoaded = true;
}

void Library::unload()
{
	assert(mLoaded);
	LIBRARY_UNLOAD(mHandle);
	mLoaded = false;
}

void* Library::getSymbol(const std::string &name)
{
	if (!mLoaded)
		load();

	return LIBRARY_SYMBOL(mHandle, name.c_str());
}