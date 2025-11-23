# Tutorial: Develop Your First Plugin

This tutorial will guide you through creating a new plugin from scratch. We will build a `MultiplierService` plugin that, like the existing `DummyService`, provides an implementation for the abstract service interface defined in the `DummyApplicationCli` plugin.

Instead of adding numbers, our new plugin will multiply them.

## Prerequisites

Before starting, ensure you have a complete and working project setup as detailed in the **"00_Getting_Started"** tutorial. You should be able to build and run the `Main.exe` successfully from Visual Studio.

## Step 1: Create the Plugin's Directory Structure

First, we need to create a home for our new plugin's source code.

Navigate to the `Sources/Plugins/` directory and create a new folder named `MultiplierService`.

Inside `Sources/Plugins/MultiplierService/`, create the following empty files. We will add content to them in the next steps.

```
MultiplierService/
├── Plugin.xml
├── Build.h
├── Service.h
├── Service.cpp
└── main.cpp
```

## Step 2: Integrate into the Main Build (`CMakeLists.txt`)

Instead of creating a new `CMakeLists.txt` for our plugin, we will add its build rules directly to the root `CMakeLists.txt` file. This centralizes the project's build configuration.

Open the main `CMakeLists.txt` file located in the project's root directory. Scroll down to the `# Plugins` section and add the following CMake code, for instance, after the `PluginDummyService` block:

```cmake
## MultiplierService

add_library(PluginMultiplierService SHARED
	"Sources/Plugins/MultiplierService/Build.h"
	"Sources/Plugins/MultiplierService/main.cpp"
	"Sources/Plugins/MultiplierService/Service.h"
	"Sources/Plugins/MultiplierService/Service.cpp")

target_link_libraries(PluginMultiplierService Core)
target_link_libraries(PluginMultiplierService PluginDummyApplicationCli)

configure_file("Sources/Plugins/MultiplierService/Plugin.xml" "PluginMultiplierService.xml")
```

This code accomplishes the following:
*   `add_library(PluginMultiplierService ...)`: Defines a shared library target for our plugin, named according to the `Plugin<Name>` convention.
*   `target_link_libraries(...)`: Links our new plugin against the `Core` framework and `PluginDummyApplicationCli`, since we are implementing its service interface.
*   `configure_file(...)`: Copies the plugin's manifest from its source directory to the build output directory, renaming it to `PluginMultiplierService.xml` to match the library name.

## Step 3: Create the Plugin Manifest (`Plugin.xml`)

The manifest file describes our plugin to the framework, including the services it provides and the dependencies it requires.

Copy the following into `Sources/Plugins/MultiplierService/Plugin.xml`:

```xml
<Plugin name="Plugins::MultiplierService">
  <Services>
    <Service name="Service" extends="Plugins::DummyApplicationCli::Service"/>
  </Services>
  <Dependencies>
    <Dependency plugin="Plugins::DummyApplicationCli"/>
  </Dependencies>
</Plugin>
```
This defines a plugin named `Plugins::MultiplierService`. The `extends` attribute points to `Plugins::DummyApplicationCli::Service`, telling the framework that our service is a concrete implementation of the abstract `Service` interface defined in the `DummyApplicationCli` plugin.

## Step 4: Add Boilerplate Code (`Build.h`)

This header file is used to manage symbol visibility (`dllexport`/`dllimport`) for the shared library.

**`Build.h`:**
```cpp
#pargma once

#include <Core/Platform.h>

#ifdef Plugins_MultiplierService_EXPORTS
#	define PLUGIN_MULTIPLIER_SERVICE_API CORE_EXPORT
#else
#	define PLUGIN_MULTIPLIER_SERVICE_API CORE_IMPORT
#endif

#endif
```

## Step 5: Define and Implement the Service

Now we'll write the core logic of our plugin. Our `MultiplierService` will provide an implementation for the `calculate` method defined in the `DummyApplicationCli`'s abstract service.

**`Service.h` (The Header):**
This file defines our `Service` class, which inherits from `Plugins::DummyApplicationCli::Service`.
```cpp
#pargma once

#include "Build.h"
#include <Plugins/DummyApplicationCli/Service.h> // The interface we are implementing
#include <boost/shared_ptr.hpp>

namespace Plugins
{
	namespace MultiplierService
	{
		class PLUGIN_MULTIPLIER_SERVICE_API Service : public Plugins::DummyApplicationCli::Service
		{
		public:
			// The implementation of the abstract 'calculate' method
			virtual int calculate(int a, int b);
		};

		typedef boost::shared_ptr<Service> ServicePtr;
	}
}

#endif
```

**`Service.cpp` (The Implementation):**
Here, we provide our unique logic for the `calculate` method: multiplication.
```cpp
#include "Service.h"

using namespace Plugins::MultiplierService;

int Service::calculate(int a, int b)
{
	// Our implementation returns the product of a and b
	return a * b;
}
```

## Step 6: Register the Service (`main.cpp`)

This final piece of code creates and registers a factory function with the framework. The `Plugin` class will use this factory to create instances of our `Service` class at runtime.

**`main.cpp`:**
```cpp
#include "Service.h"
#include <Core/Factory.h>

using namespace Plugins::MultiplierService;

// Register our Service class with the framework
typedef Core::Factory<Service> Factory;
DECLARE_SERVICE_FACTORY(Factory)
```

## Step 8: Build and Run!

Return to Visual Studio. The IDE should detect the changes to the CMake files and automatically re-configure the project. If not, you can trigger it by saving the modified `Sources/Plugins/CMakeLists.txt` file.

Now, **Build > Build All** (`Ctrl+Shift+B`) to compile your new plugin.

Finally, run the application by pressing **F5**. The console output should now show both the `DummyService` and your new `MultiplierService` being called:

```
Dienstimplementierung Plugins::DummyService::Service
calculate(1, 1) = 2
Dienstimplementierung Plugins::MultiplierService::Service
calculate(1, 1) = 1
Hello world!
```

Congratulations! You have successfully created, integrated, and used your first plugin.
