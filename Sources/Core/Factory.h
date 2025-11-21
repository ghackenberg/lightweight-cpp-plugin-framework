#ifndef CORE_FACTORY_H
#define CORE_FACTORY_H

#include "Build.h"
#include "Service.h"
#include <string>
#include <memory>

namespace Core
{

	/// The end of the service chain.
	struct FactoryChainEnd
	{
		/// Throw an error.
		static Service* getService(const std::string &name)
		{
			throw "Service not supported!";
		}
	};

	/// Template-based service factory implementation.
	template <class ServiceType, class FactoryChain = FactoryChainEnd>
	struct Factory
	{
		/// Return the own service or forward the request to the next item in the template chain.
		static Service* getService(const std::string &name)
		{
			if (typeid(ServiceType).name() == name)
				return new ServiceType();
			else
				return FactoryChain::getService(name);
		}
	};

	/// Plugin load function pointer.
	typedef Service* (*ServiceGetter)(const std::string &name);

}

/// Plugin declaration macro.
#define DECLARE_SERVICE_FACTORY(classname) \
	CORE_EXTERN CORE_EXPORT Core::Service* getService(const std::string &name)\
	{\
		return classname::getService(name);\
	}

#endif