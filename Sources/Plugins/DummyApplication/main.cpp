#include "Application.h"
#include <Core/Factory.h>

using namespace Plugins::DummyApplication;

typedef Core::Factory<Application> Factory;

DECLARE_SERVICE_FACTORY(Factory)