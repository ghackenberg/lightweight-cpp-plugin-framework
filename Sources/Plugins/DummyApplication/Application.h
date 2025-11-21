#pragma once

#include "Build.h"
#include <Core/Application.h>
#include <memory>

namespace Plugins
{
	namespace DummyApplication
	{

		/// Sample application service.
		class PLUGINS_DUMMYAPPLICATION_API Application : public Core::Application
		{
		public:

			/// Run implementation.
			virtual int run(int argc, char **argv);

		};

		/// Shared application object.
		typedef std::shared_ptr<Application> ApplicationPtr;

	}
}