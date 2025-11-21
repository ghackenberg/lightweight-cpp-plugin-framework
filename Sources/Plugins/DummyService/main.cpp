#include "Service.h"
#include <Core/Factory.h>

using namespace Plugins::DummyService;

typedef Core::Factory<Service> Factory;

DECLARE_SERVICE_FACTORY(Factory)