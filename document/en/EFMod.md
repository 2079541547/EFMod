### Directory Structure

Assuming our working directory is `example`, and we wish to create a mod named `MyMod` within this directory, the directory structure would be as follows:

```
example/
├── MyMod/
│   ├── Executable/
│   │   ├── arm64-v8a/
│   │   │   └── libMyMod.so
│   │   ├── armeabi-v7a/
│   │   │   └── libMyMod.so
│   │   ├── x86/
│   │   │   └── libMyMod.so
│   │   └── x86_64/
│   │       └── libMyMod.so
│   ├── Page/
│   │   └── index.html  # The HTML file for the user interface
│   ├── Private/
│   │   └── private_data.txt  # A private data file
│   ├── icon.png  # The mod's icon
│   ├── info.json  # The mod's information file
│   ├── include/  # Directory containing header files (not part of the build process)
│   │   ├── EFMod.hpp  # Header file for the mod base class
│   │   └── EFModLoaderAPI.hpp  # Header file for the loader API
│   ├── src/  # Source code directory (not part of the build process)
│   │   └── main.cpp  # The main file of the mod
│   └── CMakeLists.txt  # Build script (not part of the build process)
```

### Fixed Header Files

#### `include/EFMod.hpp`

```cpp
//
// Created by example_author on 2024/10/13.
//
#pragma once

#include <string>

class EFMod {
public:
    virtual ~EFMod() {}

    // Get the unique identifier of the mod
    virtual const char* GetIdentifier() const = 0;

    // Called when initializing the mod
    virtual bool Initialize() = 0;

    // Registers the locations to hook and the function pointers after hooking
    virtual void RegisterHooks() = 0;

    // Registers APIs
    virtual void RegisterAPIs() = 0;

    // Receives the set of APIs provided by the loader
    virtual void LoadEFMod(EFModLoaderAPI* api) = 0;
};
```

#### `include/EFModLoaderAPI.hpp`

```cpp
//
// Created by example_author on 2024/10/13.
//
#pragma once

#include <map>
#include <string>
#include <vector>
#include <mutex>

class EFModLoaderAPI final {
public:
    // Registers an extension function for the mod
    void RegisterExtension(const std::string& extensionPoint, uintptr_t hook);

    // Registers an API (called by the Mod)
    void RegisterAPI(const std::string& APIPoint, uintptr_t Api);

    // Finds the set of extension functions
    std::vector<uintptr_t> FindHooks(const std::string& extensionPoint);

    // Finds the set of APIs
    std::vector<uintptr_t> FindAPIS(const std::string& APIPoint);

    // Gets the singleton instance
    static EFModLoaderAPI& GetEFModLoader();

private:
    // Stores the sets of extension function pointers
    std::map<std::string, std::vector<uintptr_t>> extensions;
    std::mutex extensionsMutex;

    // Stores the list of registered APIs for redirection
    std::map<std::string, std::vector<uintptr_t>> APIS;
    std::mutex APISMutex;

    // Private constructor
    EFModLoaderAPI() {}
};

// Implement the method to get the singleton instance
inline EFModLoaderAPI& EFModLoaderAPI::GetEFModLoader() {
    static EFModLoaderAPI instance;
    return instance;
}

// Implement the RegisterExtension method
inline void EFModLoaderAPI::RegisterExtension(const std::string& extensionPoint, uintptr_t hook) {
    std::lock_guard<std::mutex> lock(extensionsMutex);
    extensions[extensionPoint].push_back(hook);
}

// Implement the RegisterAPI method
inline void EFModLoaderAPI::RegisterAPI(const std::string &APIPoint, uintptr_t Api) {
    std::lock_guard<std::mutex> lock(APISMutex);
    APIS[APIPoint].push_back(Api);
}

// Implement the FindHooks method
inline std::vector<uintptr_t> EFModLoaderAPI::FindHooks(const std::string& extensionPoint) {
    std::lock_guard<std::mutex> lock(extensionsMutex);
    auto it = extensions.find(extensionPoint);
    if (it == extensions.end()) {
        return {};
    }
    return it->second;
}

// Implement the FindAPIS method
inline std::vector<uintptr_t> EFModLoaderAPI::FindAPIS(const std::string& APIPoint) {
    std::lock_guard<std::mutex> lock(APISMutex);
    auto it = APIS.find(APIPoint);
    if (it == APIS.end()) {
        return {};
    }
    return it->second;
}
```

### Example Mod Source Code

#### `src/main.cpp`

```cpp
//
// Created by example_author on 2024/10/13.
//
#include <iostream>
#include <vector>
#include <string>
#include <android/log.h>
#include "../include/EFMod.hpp" // Include EFMod header
#include "../include/EFModLoaderAPI.hpp" // Include EFModLoaderAPI header

// Define the mod class
class ExampleMod : public EFMod {
public:
    // Get the unique identifier of the mod
    const char* GetIdentifier() const override {
        return "ExampleMod"; // Returns the unique identifier of the mod
    }

    // Called when initializing the mod
    bool Initialize() override {
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Initializing mod: %s", GetIdentifier());
        return true; // Returns true upon successful initialization
    }

    // Registers the locations to hook and the function pointers after hooking
    void RegisterHooks() override {
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Registering hooks for mod: %s", GetIdentifier());

        // Register hook points
        std::vector<std::pair<std::string, uintptr_t>> hooks{
            {"Assembly-CSharp.dll.Terraria.Main.DamageVar", reinterpret_cast<uintptr_t>(&ModifyDamage)} // Register the hook function
        };

        // Iterate and register hooks
        for (const auto& [hookPoint, funcPtr] : hooks) {
            modAPI->RegisterExtension(hookPoint, funcPtr); // Register the hook with the Loader-provided API
        }
    }

    // Registers APIs
    void RegisterAPIs() override {
        // Registers APIs (if needed)
        modAPI->RegisterAPI("ExampleAPI", reinterpret_cast<uintptr_t>(&ExampleAPI));
    }

    // Receives the set of APIs provided by the loader
    void LoadEFMod(EFModLoaderAPI* api) override {
        // Save mod information
        modAPI = api; // Save the instance of the API provided by the loader
    }

private:
    EFModLoaderAPI* modAPI = nullptr; // Saves the pointer to EFModLoaderAPI

    // Example extension function
    void ModifyDamage() {
        // Implement the logic for modifying damage
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Modifying damage...");
    }

    // Example API function
    void ExampleAPI() {
        // Implement the logic for the API
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Example API called...");
    }
};

// Export the mod instance
extern "C" EFMod* GetModInstance() {
    static ExampleMod modInstance; // Create a static mod instance
    return &modInstance; // Return the address of the mod instance
}
```

### Build Script

#### `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)

project(MyMod)

set(CMAKE_CXX_STANDARD 14)

add_library(MyMod SHARED
    src/main.cpp
)

target_include_directories(MyMod PUBLIC ../include)

install(TARGETS MyMod DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Executable/${CMAKE_SYSTEM_PROCESSOR})
```

### `info.json` File

```json
{
  "SpecialLoading": false,
  "enablePrivate": false,
  "customizePage": false,
  "openSource": false,
  "openSourceUrl": "",
  "ModName": "MyMod",
  "Author": "ExampleAuthor",
  "Identifier": "ExampleMod-ExampleAuthor",
  "Introduce": "This is an example mod",
  "Version": "1.0.0"
}
```

### Directory Explanation

1. **`MyMod/`**
   
   - The root directory of the mod, which contains all files related to the mod.
2. **`MyMod/Executable/`**
   
   - This directory contains the executable files or dynamic libraries of the mod for different architectures.
   - Each subdirectory corresponds to different CPU architectures:
     - **`arm64-v8a/`**: Library for the ARM64 architecture.
     - **`armeabi-v7a/`**: Library for the ARMv7 architecture.
     - **`x86/`**: Library for the x86 architecture.
     - **`x86_64/`**: Library for the x86_64 architecture.
3. **`MyMod/Page/`**
   
   - This directory contains files related to the user interface, such as HTML, CSS, and JavaScript.
   - For example, `index.html` might be the settings page of the mod.
4. **`MyMod/Private/`**
   
   - This directory stores private data of the mod, which is visible only to the mod itself.
   - For example, `private_data.txt` might contain data that only this mod needs to access.
5. **`MyMod/icon.png`**
   
   - The icon file of the mod, used for identifying the mod in the mod manager.
6. **`MyMod/info.json`**
   
   - The information file of the mod, which contains metadata about the mod such as name, version, author, etc.
7. **`MyMod/include/`**
   
   - Directory containing header files, including `EFMod.hpp` and `EFModLoaderAPI.hpp`.
8. **`MyMod/src/`**
   
   - Source code directory, containing source code files of the mod.
9. **`MyMod/CMakeLists.txt`**
   
   - Build script used to compile the mod and generate the dynamic library.

With these steps, you can create a complete mod and understand its directory structure and file content. This will help you better manage and develop mods.

