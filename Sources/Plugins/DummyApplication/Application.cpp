#include "Application.h"
#include "Service.h"
#include <Core/Root.h>
#include <iostream>

using namespace Plugins::DummyApplication;

int Application::run(int argc, char **argv)
{
	Core::Root *root = Core::Root::getInstance();

	Core::Root::ServiceList implementations = root->getImplementations("Plugins::DummyApplication::Service");

	for (Core::Root::ServiceList::const_iterator iterator = implementations.begin(); iterator != implementations.end(); iterator++)
	{
		std::cout << "Dienstimplementierung " << iterator->first << "::" << iterator->second << std::endl;

		Core::PluginPtr plugin = root->getPlugin(iterator->first);

		ServicePtr service = plugin->getService<Plugins::DummyApplication::Service>(iterator->second);

		std::cout << service->calculate(1, 1) << std::endl;
	}

	std::cout << "Hello world!" << std::endl;
	std::cin.get();

	return 0;
}