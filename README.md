# Lightweight C++ Plugin Framework

![](./Images/SocialPreview.jpg)

This framework provides a simple yet powerful architecture for building modular C++ applications. It was born from the need for a dependency-light, cross-platform plugin system that avoids the complexity of larger frameworks. The core motivation is to enable true "drop-in" extensibility: new functionality can be added by simply placing a plugin into a folder, with no need to recompile the core application.

The architecture's power is rooted in the separation of interfaces and implementations. A plugin can define an **abstract service**, which acts as a contract or an "extension point" for a certain capability. Other, independent plugins can then provide **concrete service** implementations that fulfill this contract. For example, a core plugin could define an abstract "ImageEffect" service, and then separate plugins could implement "GaussianBlur", "Sharpen", and "Invert" effects. This promotes a highly decoupled system where extension points are clearly defined and independently implemented.

This approach is ideal for a wide range of software, from desktop tools like image editors and digital audio workstations to game engines that require custom behaviors. Looking forward, the design is well-suited for modern deployment scenarios like **WebAssembly (WASM)**. An application compiled to WASM could dynamically load plugins as separate `.wasm` modules, enabling high-performance, extensible web applications where features are loaded on demand.

## Dependencies

This framework leverages several external libraries to provide its core functionalities. Dependencies are categorized by when they are needed: during compilation (build-time) or when the application is running (run-time).

```mermaid
flowchart
  subgraph "Build- and run-time"
    Boost
  end
  subgraph "Build-time only"
    direction TB
    CMake
    vcpkg
  end
```

### *Build*-time **only**

These dependencies are crucial for setting up the development environment and compiling the project:

*   **CMake**: The cross-platform build system used to configure and generate the project builds.
*   **vcpkg**: A C++ package manager used to install and manage library dependencies. The required libraries are listed in the `vcpkg.json` file in the root directory.

### Build- **and** run-time

These libraries are essential both for building the project and for its operation at runtime, handling common tasks like memory management and data parsing:

*   **Boost**: A collection of high-quality, peer-reviewed C++ libraries. This framework uses Boost for various utilities, including smart pointers (`boost::shared_ptr`).

## Tutorials

This project includes step-by-step tutorials to help you get started with the framework.

*   **[00 - Getting Started](./Tutorials/00_Getting_Started/README.md)**: This guide walks you through cloning the repository, setting up the development environment on Windows with Visual Studio 2026, and building and running the project for the first time. It covers the automatic dependency installation via vcpkg and how to launch the main application.

*   **[01 - Develop Your First Plugin](./Tutorials/01_Develop_Your_First_Plugin/README.md)**: Learn how to create a new plugin from scratch. This tutorial demonstrates how to build a `MultiplierService` that implements an existing abstract service, configure its build system with CMake, create its manifest file, and integrate it into the main application.

*   **[02 - Understand The Core](./Tutorials/02_Understand_The_Core/README.md)**: Dive into the fundamental components of the framework, understanding the roles of the `Registry`, `Plugin`, `Service`, and `Application` classes and how they interact to provide a robust and extensible architecture.