#ifndef PLUGINS_DUMMYAPPLICATION_APPLICATION_H
#define PLUGINS_DUMMYAPPLICATION_APPLICATION_H

#include "Build.h"
#include <Core/Application.h>
#include <boost/shared_ptr.hpp>

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
		typedef boost::shared_ptr<Application> ApplicationPtr;

	}
}

#endif