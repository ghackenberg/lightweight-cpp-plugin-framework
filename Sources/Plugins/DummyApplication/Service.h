#ifndef PLUGINS_DUMMYAPPLICATION_SERVICE_H
#define PLUGINS_DUMMYAPPLICATION_SERVICE_H

#include "Build.h"
#include <Core/Service.h>
#include <boost/shared_ptr.hpp>

namespace Plugins
{
	namespace DummyApplication
	{

		/// Sample service.
		class PLUGINS_DUMMYAPPLICATION_API Service : public Core::Service
		{
		public:

			/// Calculate method.
			virtual int calculate(int a, int b) = 0;

		};

		/// Shared service object.
		typedef boost::shared_ptr<Service> ServicePtr;

	}
}

#endif