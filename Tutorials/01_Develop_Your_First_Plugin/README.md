# Tutorial: Develop Your First Plugin

This tutorial will guide you through creating a new plugin from scratch. We will build a `MultiplierService` plugin that, like the existing `DummyService`, provides an implementation for the abstract service interface defined in the `DummyApplication` plugin.

Instead of adding numbers, our new plugin will multiply them.

## Prerequisites

Before starting, ensure you have a complete and working project setup as detailed in the **"00_Getting_Started"** tutorial. You should be able to build and run the `Main.exe` successfully from Visual Studio.

## Step 1: Create the Plugin's Directory Structure

First, we need to create a home for our new plugin's source code.

Navigate to the `Sources/Plugins/` directory and create a new folder named `MultiplierService`.

Inside `Sources/Plugins/MultiplierService/`, create the following empty files. We will add content to them in the next steps.

```
MultiplierService/
├── CMakeLists.txt
├── Plugin.xml
├── Build.h
├── Namespace.h
├── Service.h
├── Service.cpp
└── main.cpp
```

## Step 2: Configure the Build System (`CMakeLists.txt`)

This file tells CMake how to build our plugin as a shared library (`.dll`) and links it against the necessary dependencies.

Copy the following code into `Sources/Plugins/MultiplierService/CMakeLists.txt`:

```cmake
# Define the shared library target for our plugin
add_library(Plugins_MultiplierService SHARED
	Build.h
	Namespace.h
	main.cpp
	Service.h
	Service.cpp)

# Link against the core framework
target_link_libraries(Plugins_MultiplierService Core)

# Link against the DummyApplication plugin, since we use its service interface
target_link_libraries(Plugins_MultiplierService Plugins_DummyApplication)

# Copy the manifest file to the build output directory
configure_file(Plugin.xml Plugin.xml)
```

## Step 3: Create the Plugin Manifest (`Plugin.xml`)

The manifest file describes our plugin to the framework.

Copy the following into `Sources/Plugins/MultiplierService/Plugin.xml`:

```xml
<Plugin name="Plugins::MultiplierService">
  <Services>
    <Service name="Service" extends="Plugins::DummyApplication::Service"/>
  </Services>
  <Dependencies>
    <Dependency plugin="Plugins::DummyApplication"/>
  </Dependencies>
</Plugin>
```
This defines a plugin named `Plugins::MultiplierService` that provides one `Service`. The `extends` attribute tells the framework that our service is a concrete implementation of the abstract service from `Plugins::DummyApplication`. We also declare a dependency on that plugin.

## Step 4: Add Boilerplate Code (`Build.h`, `Namespace.h`)

These files help with exporting symbols and documenting the namespace.

**`Build.h`:**
```cpp
#ifndef PLUGINS_MULTIPLIERSERVICE_BUILD_H
#define PLUGINS_MULTIPLIERSERVICE_BUILD_H

#include <Core/Platform.h>

#ifdef Plugins_MultiplierService_EXPORTS
#	define PLUGINS_MULTIPLIERSERVICE_API CORE_EXPORT
#else
#	define PLUGINS_MULTIPLIERSERVICE_API CORE_IMPORT
#endif

#endif
```

**`Namespace.h`:**
```cpp
/**
 * \namespace Plugins::MultiplierService
 * \brief A sample plugin that implements the DummyApplication::Service interface.
 */
```

## Step 5: Define and Implement the Service

Now we'll write the core logic of our plugin.

**`Service.h` (The Header):**
This file defines our `Service` class. Notice it inherits from `Plugins::DummyApplication::Service`.
```cpp
#ifndef PLUGINS_MULTIPLIERSERVICE_SERVICE_H
#define PLUGINS_MULTIPLIERSERVICE_SERVICE_H

#include "Build.h"
#include <Plugins/DummyApplication/Service.h> // The interface we are implementing
#include <boost/shared_ptr.hpp>

namespace Plugins
{
	namespace MultiplierService
	{
		class PLUGINS_MULTIPLIERSERVICE_API Service : public Plugins::DummyApplication::Service
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
Here we provide the logic for the `calculate` method: multiplication.
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

This final piece of code creates the factory function that allows the framework to create instances of our service class.

**`main.cpp`:**
```cpp
#include "Service.h"
#include <Core/Registry.h>

using namespace Plugins::MultiplierService;

// Register our Service class with the framework
typedef Core::Registry<Service> Registry;
DECLARE_SERICE_REGISTRY(Registry)
```

## Step 7: Add the Plugin to the Main Build

The last step is to tell the main project's build system that our new plugin exists.

Open the file `Sources/Plugins/CMakeLists.txt` and add a new line to include the `MultiplierService` directory:

```cmake
# ... existing add_subdirectory calls
add_subdirectory(DummyApplication)
add_subdirectory(DummyService)

# Add this line:
add_subdirectory(MultiplierService)
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
