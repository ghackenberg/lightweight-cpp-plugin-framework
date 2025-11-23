#include <Core/Registry.h>
#include <Core/Plugin.h>
#include <Core/Application.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <filesystem>
#include <fstream>

/// Load the configuration file and execute the specified application.
int main(int argc, char **argv)
{
	try
	{
		// Get registry instance
		Core::Registry* registry = Core::Registry::getInstance();

		// Add plugin folder
		registry->addPluginFolder(std::filesystem::path(argv[0]).parent_path().string());

#ifndef _NDEBUG
		std::ofstream out;
		out.open("ExtensionMap.txt");
		registry->dumpPlugins(out);
		out.close();
#endif

		// Read configuration file
		boost::property_tree::ptree tree;
		boost::property_tree::read_xml("Configuration.xml", tree);

		// Get plugin and application service name
		std::string pluginName(tree.get<std::string>("Configuration.Application.<xmlattr>.plugin"));
		std::string serviceName(tree.get<std::string>("Configuration.Application.<xmlattr>.service"));

		// Get plugin and application service instance
		Core::PluginPtr plugin = registry->getPlugin(pluginName);
		Core::ApplicationPtr service = plugin->getService<Core::Application>(serviceName);

		// Run application service
		return service->run(argc, argv);
	}
	catch (...)
	{
		return 1;
	}
}