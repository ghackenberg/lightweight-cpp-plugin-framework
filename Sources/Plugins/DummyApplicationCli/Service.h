#pragma once

#include "Build.h"
#include <Core/Service.h>
#include <memory>

namespace Plugins
{
	namespace DummyApplicationCli
	{

		/// Sample service.
		class PLUGINS_DUMMYAPPLICATIONCLI_API Service : public Core::Service
		{
		public:

			/// Calculate method.
			virtual int calculate(int a, int b) = 0;

		};

		/// Shared service object.
		typedef std::shared_ptr<Service> ServicePtr;

	}
}