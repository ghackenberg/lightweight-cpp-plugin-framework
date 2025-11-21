#ifndef CORE_SERVICE_H
#define CORE_SERVICE_H

#include "Build.h"
#include <memory>

namespace Core
{

	/// Base class for the plugin services.
	class CORE_API Service
	{
	public:

		/// Virtual destructor for overloading.
		virtual ~Service();

	};

	/// Shared service object.
	typedef std::shared_ptr<Service> ServicePtr;

}

#endif