#pragma once

#include "Build.h"
#include <Core/Application.h>
#include <memory>

namespace Plugins
{
	namespace DummyApplicationCli
	{

		/// Sample application service.
		class PLUGIN_DUMMY_APPLICATION_CLI_API Application : public Core::Application
		{
		public:

			/// Run implementation.
			virtual int run(int argc, char **argv);

		};

		/// Shared application object.
		typedef std::shared_ptr<Application> ApplicationPtr;

	}
}