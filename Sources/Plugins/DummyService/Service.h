#ifndef PLUGINS_DUMMYSERVICE_SERVICE_H
#define PLUGINS_DUMMYSERVICE_SERVICE_H

#include "Build.h"
#include <Plugins/DummyApplication/Service.h>
#include <boost/shared_ptr.hpp>

namespace Plugins
{
	namespace DummyService
	{

		/// Sample service.
		class PLUGINS_DUMMYSERVICE_API Service : public Plugins::DummyApplication::Service
		{
		public:

			/// Calculate method.
			virtual int calculate(int a, int b);

		};

		/// Shared service object.
		typedef boost::shared_ptr<Service> ServicePtr;

	}
}

#endif