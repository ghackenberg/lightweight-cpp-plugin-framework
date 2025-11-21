#include <Core/Registry.h>
#include <Core/Plugin.h>
#include <Core/Application.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <fstream>

using namespace Core;
using namespace boost;

/// Load the configuration file and execute the specified application.
int main(int argc, char **argv)
{
	Registry* registry = Registry::getInstance();

	// Read the configuration
	property_tree::ptree tree;
	property_tree::read_xml("Configuration.xml", tree);

	// Add the plugin folders
	property_tree::ptree folders(tree.get_child("Configuration.PluginFolders"));

	for (property_tree::ptree::iterator iter = folders.begin(); iter != folders.end(); iter++)
	{
		std::string path(iter->second.get<std::string>("<xmlattr>.path"));
		registry->addPluginFolder(path);
	}

#ifndef _NDEBUG
	std::ofstream out;
	out.open("ExtensionMap.txt");
	registry->dumpPlugins(out);
	out.close();
#endif

	// Start the application
	std::string pluginName(tree.get<std::string>("Configuration.Application.<xmlattr>.plugin"));
	std::string serviceName(tree.get<std::string>("Configuration.Application.<xmlattr>.service"));

	PluginPtr plugin = registry->getPlugin(pluginName);
	ServicePtr service = plugin->getService(serviceName);
	ApplicationPtr application = boost::dynamic_pointer_cast<Application>(service);

	return application->run(argc, argv);
}