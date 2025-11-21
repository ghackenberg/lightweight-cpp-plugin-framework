#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

#include "Build.h"
#include "Library.h"
#include "Factory.h"
#include "Service.h"
#include <string>
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

namespace Core
{
	/// Forward declaration for SWIG.
	class Service;

	/// Shared pointer definition for SWIG.
	typedef boost::shared_ptr<Service> ServicePtr;
	
	/// Base class for plugins.
	class CORE_API Plugin
	{
	public:

		/// Definition of a service in the plugin descriptor.
		struct ServiceDeclaration
		{
			enum Type { ABSTRACT, CONCRETE };

			/// Create a new service declaration object.
			ServiceDeclaration(const boost::property_tree::ptree &props, const std::string &name, const std::string &extends, Type type);

			/// The boost property tree.
			boost::property_tree::ptree properties;
			/// The name of the service.
			std::string                 name;
			/// The base class of the service.
			std::string                 extends;
			/// The type of the service (concrete or abstract).
			Type                        type;

			/// The service instance.
			ServicePtr  instance;
		};

		/// Map of service declarations by name.
		typedef std::map<std::string, ServiceDeclaration> ServiceMap;
		/// List of plugin dependencies.
		typedef std::list<std::string>                    DependencyList;

	public:

		/// Construct a plugin object.
		Plugin(const std::string &path);

		/// Retrieve the path of the plugin.
		const std::string &getPath() const
		{
			return mPath;
		}
		/// Retrieve the name of the plugin.
		const std::string &getName() const
		{
			return mName;
		}
		/// Retrieve the dependency list.
		const DependencyList &getDependencyList() const
		{
			return mDependencyList;
		}
		/// Retrieve the service map.
		const ServiceMap &getServiceMap() const
		{
			return mServiceMap;
		}

		/// Retrieve a specific service declaration.
		const ServiceDeclaration &getServiceDeclaration(const std::string &name) const;

		/// Get a service by name.
		ServicePtr getService(const std::string &name);
		/// Get a service by type info.
		ServicePtr getService(const std::type_info &type);

		/// Get a casted service by name.
		template <class ServiceType>
		boost::shared_ptr<ServiceType> getService(const std::string &name)
		{
			return boost::dynamic_pointer_cast<ServiceType>(getService(name));
		}
		/// Get a casted service by type id.
		template <class ServiceType>
		boost::shared_ptr<ServiceType> getService(const std::type_info &type)
		{
			return boost::dynamic_pointer_cast<ServiceType>(getService(type));
		}
		/// Get a casted service by type.
		template <class ServiceType>
		boost::shared_ptr<ServiceType> getService()
		{
			return getService<ServiceType>(typeid(ServiceType));
		}

		/// Load the plugin shared library.
		void loadLibrary()
		{
			mLibrary->load();
		}

	private:

		/// Get a service by type id key.
		ServicePtr getServiceByKey(const std::string &key);

		/// Load the plugin DLL and all the dependencies.
		void load();

	private:

		/// The plugin path.
		std::string    mPath;
		/// The plugin name.
		std::string    mName;
		/// The associated shared library.
		LibraryPtr     mLibrary;
		/// The service cache.
		ServiceMap     mServiceMap;
		/// The dependency list.
		DependencyList mDependencyList;
		/// The dll function pointer.
		ServiceGetter  mServiceGetter;

	};

	/// Shared plugin object.
	typedef boost::shared_ptr<Plugin> PluginPtr;

}

#endif