# EFMod

* An efficient, free, universal, and intrusive Mod
* Note: If you use the source code of EFModLoader in any form, you must open-source your work. The EFMod.hpp and EFModLoaderAPI.hpp header files are not included under the AGPL3 license, so you can use these two header files without having to open-source your project.

## What Can EFMod Do?

* Anything you can imagine!
* Primarily used for game mods, such as modifying game values and adding items.

## How Is It Implemented?

* EFModLoader - This is the mod loader, which is quite important.
* EFMod - The mod itself, including the API.

## Principles?

* Directly modifies the game through injection techniques, such as Hooking, followed by loading the mod.
* EFModLoader is used to load the mods, primarily written in C++, allowing the registration of APIs present in EFModLoader and extending game functions.
  
  ## Loading Principle
  
  ```C++
  ...
  
  // Get the mod instance
  EFMod* (*getModInstance)();
  getModInstance = (EFMod* (*)())dlsym(handle, "GetModInstance");
  if (!getModInstance) {
      dlclose(handle);
      return;
  }
  
  EFMod* mod = getModInstance();
  assert(mod && "Mod instance is null");
  
  // Provide the set of APIs to the mod
  mod->LoadEFMod(&EFModLoaderAPI::GetEFModLoader());
  
  // Store the mod instance
  loadedMods[mod->GetIdentifier()] = mod;
  
  // Automatically register extension functions
  mod->RegisterAPIs();
  mod->RegisterHooks();
  
  RegisterApi::Register(); // Register APIs
  
  ...
  ```
  
  * Yes, it's that simple. There's no complex implementation; this is the code from the official EFModLoader.
  
  ## EFMod Implementation
  
  ```C++
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
  
  * Your mod just needs to inherit from this class.

## [Developer Documentation](document/en/README.md)

