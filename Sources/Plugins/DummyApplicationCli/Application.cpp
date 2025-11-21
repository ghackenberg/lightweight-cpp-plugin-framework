#include "Application.h"
#include "Service.h"
#include <Core/Registry.h>
#include <iostream>

using namespace Plugins::DummyApplicationCli;

int Application::run(int argc, char **argv)
{
	Core::Registry *registry = Core::Registry::getInstance();

	Core::Registry::ServiceList implementations = registry->getImplementations("Plugins::DummyApplicationCli::Service");

	for (Core::Registry::ServiceList::const_iterator iterator = implementations.begin(); iterator != implementations.end(); iterator++)
	{
		std::cout << "Dienstimplementierung " << iterator->first << "::" << iterator->second << std::endl;

		Core::PluginPtr plugin = registry->getPlugin(iterator->first);

		ServicePtr service = plugin->getService<Plugins::DummyApplicationCli::Service>(iterator->second);

		std::cout << "calculate(1, 1) = " << service->calculate(1, 1) << std::endl;
	}

	std::cout << "Hello world!" << std::endl;
	std::cin.get();

	return 0;
}