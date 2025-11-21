#include "Application.h"
#include <Core/Factory.h>

using namespace Plugins::DummyApplicationGui;

typedef Core::Factory<Application> Factory;

DECLARE_SERVICE_FACTORY(Factory)