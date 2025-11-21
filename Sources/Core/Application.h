#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include "Build.h"
#include "Service.h"
#include <boost/shared_ptr.hpp>

namespace Core
{

	/// Base class for application services.
	class CORE_API Application : public Service
	{
	public:

		/// Abstract run method.
		virtual int run(int argc, char **argv) = 0;

	};

	/// Shared application service.
	typedef boost::shared_ptr<Application> ApplicationPtr;

}

#endif