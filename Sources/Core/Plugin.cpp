#include "Plugin.h"
#include "Root.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace Core;
using namespace boost;

Plugin::ServiceDeclaration::ServiceDeclaration(const boost::property_tree::ptree &props, const std::string &name, const std::string &extends, Type type)
: properties(props), name(name), extends(extends), type(type)
{

}

Plugin::Plugin(const std::string &path)
: mPath(path), mServiceGetter(0)
{
	// read the config file
	property_tree::ptree conf;
	property_tree::read_xml(path + "/Plugin.xml", conf);

	// initialize the members
	mName = conf.get<std::string>("Plugin.<xmlattr>.name");

	boost::optional<property_tree::ptree> services(conf.get_child("Plugin.Services"));

	if (services)
	{
		for (property_tree::ptree::iterator iter = services->begin(); iter != services->end(); iter++)
		{
			std::string name(iter->second.get<std::string>("<xmlattr>.name"));
			optional<std::string> extends(iter->second.get_optional<std::string>("<xmlattr>.extends"));
			optional<std::string> type(iter->second.get_optional<std::string>("<xmlattr>.type"));

			ServiceDeclaration::Type typenum = ServiceDeclaration::CONCRETE;

			if (type)
				if (*type == "concrete")
					typenum = ServiceDeclaration::CONCRETE;
				else if (*type == "abstract")
					typenum = ServiceDeclaration::ABSTRACT;

			mServiceMap.insert(ServiceMap::value_type("class " + mName + "::" + name, ServiceDeclaration(iter->second, name, extends ? *extends : "", typenum)));
		}
	}

	boost::optional<property_tree::ptree> dependencies(conf.get_child_optional("Plugin.Dependencies"));

	if (dependencies)
	{
		for (property_tree::ptree::iterator iter = dependencies->begin(); iter != dependencies->end(); iter++)
		{
			std::string plugin(iter->second.get<std::string>("<xmlattr>.plugin"));

			mDependencyList.push_back(plugin);
		}
	}

	// Generate the DLL name from the plugin name
	std::string dllName(mName);
	std::string::size_type pos;

	while ((pos = dllName.find_first_of("::")) != std::string::npos)
	{
		dllName.replace(pos, 2, "_");
	}

	mLibrary.reset(new Library(path + "/" + dllName));
}

const Plugin::ServiceDeclaration &Plugin::getServiceDeclaration(const std::string &name) const
{
	ServiceMap::const_iterator iter = mServiceMap.find("class " + mName + "::" + name);

	if (iter != mServiceMap.end())
		return iter->second;
	else
		throw "Service declaration not found!";
}

ServicePtr Plugin::getService(const std::string &name)
{
	return getServiceByKey("class " + mName + "::" + name);
}

ServicePtr Plugin::getService(const std::type_info &type)
{
	return getServiceByKey(type.name());
}

ServicePtr Plugin::getServiceByKey(const std::string &key)
{
	if (mServiceGetter == 0)
	{
		load();
	}

	ServiceMap::iterator iter = mServiceMap.find(key);

	assert(iter != mServiceMap.end());

	if (!iter->second.instance.get())
		iter->second.instance.reset(mServiceGetter(key));

	return iter->second.instance;
}

void Plugin::load()
{
	if (mServiceGetter == 0)
	{
		// Load the dependencies
		for (DependencyList::iterator iter = mDependencyList.begin(); iter != mDependencyList.end(); iter++)
		{
			Root::getInstance()->getPlugin(*iter)->load();
		}

		// Load the own DLL by resolving the getter symbol
		mServiceGetter = (ServiceGetter) mLibrary->getSymbol("getService");
	}

	// Check the post condition
	assert(mServiceGetter != 0);
}