#include "Root.h"
#include <iostream>
#include <boost/filesystem.hpp>

using namespace Core;
using namespace boost;

Root* Root::mInstance = 0;

Root* Root::getInstance()
{
	if (mInstance == 0)
		mInstance = new Root();

	return mInstance;
}

Root::Root()
{

}

void Root::addPluginFolder(const std::string &path)
{
	if (filesystem::is_directory(path))
	{
		for (filesystem::directory_iterator iter(path); iter != filesystem::directory_iterator(); iter++)
			if (filesystem::exists(iter->path() / "Plugin.xml"))
				addPlugin(iter->path().string());
	}
	else
	{
		throw "Path does not exist!";
	}
}

PluginPtr Root::getPlugin(const std::string &name) const
{
	PluginMap::const_iterator iter = mPluginMap.find(name);

	if (iter != mPluginMap.end())
		return iter->second;
	else
		throw "Plugin does not exist!";
}

Root::ServiceList Root::getImplementations(const std::string &service) const
{
	ServiceList result;

	// Check if the service itself has to be added
	size_t colons = service.find_last_of("::");

	std::string pluginName(service.substr(0, colons - 1));
	std::string serviceName(service.substr(colons + 1));

	if (pluginName != "Core")
	{
		PluginPtr plugin = getPlugin(pluginName);

		const Plugin::ServiceDeclaration &declaration(plugin->getServiceDeclaration(serviceName));

		if (declaration.type == Plugin::ServiceDeclaration::CONCRETE)
			result.push_back(ServiceLocator(plugin->getName(), declaration.name));
	}

	// Add the derived services
	ServiceMap::const_iterator extensions = mExtensionMap.find(service);
	if (extensions != mExtensionMap.end())
		for (ServiceList::const_iterator iter = extensions->second.begin(); iter != extensions->second.end(); iter++)
		{
			ServiceList children = getImplementations(iter->first + "::" + iter->second);
			result.insert(result.end(), children.begin(), children.end());
		}

	return result;
}

#ifndef _NDEBUG

void Root::dumpPlugins(std::ostream &out) const
{
	out << "digraph G {" << std::endl;
	out << "\tcompound = true;" << std::endl;
	out << "\tfontsize = 9;" << std::endl;
	out << "\tnode [shape = rectangle, style = filled, fillcolor = orange, fontsize = 9];" << std::endl;

	for (PluginMap::const_iterator iter = mPluginMap.begin(); iter != mPluginMap.end(); iter++)
	{
		const Plugin::ServiceMap &services(iter->second->getServiceMap());
		const Plugin::DependencyList &dependencies(iter->second->getDependencyList());

		out << "\tsubgraph \"cluster_" << iter->first << "\" {" << std::endl;
		out << "\t\tlabel = \"" << iter->first << "\";" << std::endl;
		out << "\t\tstyle = filled;" << std::endl;
		out << "\t\tfillcolor = gray;" << std::endl;
		out << "\t\t\"" << iter->first << "\" [label = \"\", color = transparent, fillcolor = transparent];" << std::endl;

		for (Plugin::ServiceMap::const_iterator subiter = services.begin(); subiter != services.end(); subiter++)
			out << "\t\t\"" << iter->first << "::" << subiter->second.name << "\" [label = \"" << subiter->second.name << "\"];" << std::endl;

		out << "\t}" << std::endl;

		for (Plugin::DependencyList::const_iterator subiter = dependencies.begin(); subiter != dependencies.end(); subiter++)
			out << "\t\"" << (*subiter) << "\" -> \"" << iter->first << "\" [style = dashed, dir = back, lhead = \"cluster_" << iter->first << "\", ltail = \"cluster_" << (*subiter) << "\"];" << std::endl;
	}

	for (ServiceMap::const_iterator iter = mExtensionMap.begin(); iter != mExtensionMap.end(); iter++)
		for (ServiceList::const_iterator subiter = iter->second.begin(); subiter != iter->second.end(); subiter++)
			out << "\t\"" << iter->first << "\" -> \"" << subiter->first << "::" << subiter->second << "\";" << std::endl;

	out << "}";
}

#endif

void Root::addPlugin(const std::string &path)
{
	PluginPtr plugin(new Plugin(path));

	mPluginMap[plugin->getName()] = plugin;

	for (Plugin::ServiceMap::const_iterator iter = plugin->getServiceMap().begin(); iter != plugin->getServiceMap().end(); iter++)
		if (iter->second.extends != "")
			mExtensionMap[iter->second.extends].push_back(ServiceLocator(plugin->getName(), iter->second.name));
}