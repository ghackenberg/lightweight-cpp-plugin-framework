#ifndef CORE_REGISTRY_H
#define CORE_REGISTRY_H

#include "Build.h"
#include "Service.h"
#include <string>
#include <boost/shared_ptr.hpp>

namespace Core
{

	/// The end of the service chain.
	struct RegistryEnd
	{
		/// Throw an error.
		static Service* getService(const std::string &name)
		{
			throw "Service not supported!";
		}
	};

	/// Template-based service registry implementation.
	template <class ServiceType, class ServiceChain = RegistryEnd>
	struct Registry
	{
		/// Return the own service or forward the request to the next item in the template chain.
		static Service* getService(const std::string &name)
		{
			if (typeid(ServiceType).name() == name)
				return new ServiceType();
			else
				return ServiceChain::getService(name);
		}
	};

	/// Plugin load function pointer.
	typedef Service* (*ServiceGetter)(const std::string &name);

}

/// Plugin declaration macro.
#define DECLARE_SERICE_REGISTRY(classname) \
	CORE_EXTERN CORE_EXPORT Core::Service* getService(const std::string &name)\
	{\
		return classname::getService(name);\
	}

#endif