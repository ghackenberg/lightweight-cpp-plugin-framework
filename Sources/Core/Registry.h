#pragma once

#include "Build.h"
#include "Plugin.h"
#include "Service.h"
#include <list>
#include <memory>

#ifndef _NDEBUG
#	include <iostream>
#endif

namespace Core
{
	/// Singleton for accessing core functionality.
	class CORE_API Registry
	{
	public:

		/// Indication of how to locate a service.
		typedef std::pair<std::string, std::string> ServiceLocator;
		/// List of service locators.
		typedef std::list<ServiceLocator> ServiceList;
		/// Map of plugin objects by name.
		typedef std::map<std::string, PluginPtr> PluginMap;
		/// Map of service locators by name.
		typedef std::map<std::string, ServiceList> ServiceMap;

	public:

		/// Singleton accessor.
		static Registry* getInstance();

		/// Add plugins folder.
		void addPluginFolder(const std::string &path);

		/// Retrieve the map of plugins.
		const PluginMap &getPluginMap() const
		{
			return mPluginMap;
		}
		/// Retrieve a plugin pointer.
		PluginPtr getPlugin(const std::string &name) const;
		/// Retrieve a list of implementations for a service.
		ServiceList getImplementations(const std::string &service) const;

#ifndef _NDEBUG
		/// Dump the plugins in GraphViz format.
		void dumpPlugins(std::ostream &out) const;
#endif

	private:

		/// Private constructor.
		Registry();

		/// Add plugin folder.
		void addPlugin(const std::string &path);

	private:

		/// Singleton pointer.
		static Registry* mInstance;

		/// The internal plugin map.
		PluginMap  mPluginMap;
		/// The internal extension map.
		ServiceMap mExtensionMap;

	};


}