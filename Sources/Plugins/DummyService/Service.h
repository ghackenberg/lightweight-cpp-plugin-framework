#pragma once

#include "Build.h"
#include <Plugins/DummyApplicationCli/Service.h>
#include <memory>

namespace Plugins
{
	namespace DummyService
	{

		/// Sample service.
		class PLUGIN_DUMMY_SERVICE_API Service : public Plugins::DummyApplicationCli::Service
		{
		public:

			/// Calculate method.
			virtual int calculate(int a, int b);

		};

		/// Shared service object.
		typedef std::shared_ptr<Service> ServicePtr;

	}
}