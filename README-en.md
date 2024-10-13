# EFMod

## What can EFMod do?

* Anything you can imagine!
* Primarily used for game mods, such as modifying game values and adding items.
  
  ## How is it achieved?
  
  * **EFModLoader** - This is the mod loader, which is crucial.
  * **EFMod** - The mod itself, including APIs.
  
  ## Principles?
  
  * By directly modifying the game through injection methods, such as Hooking techniques, followed by mod loading.
  * The EFModLoader is used to load the mods. The mods are primarily written in C++, where they can register APIs available in the EFModLoader and extend game functions.
  
  ### Loading Principle
  
  ```C++
  ...
  // Obtain the mod instance
  EFMod* (*getModInstance)();
  getModInstance = (EFMod* (*)())dlsym(handle, "GetModInstance");
  if (!getModInstance) {
      dlclose(handle);
      return;
  }
  
  EFMod* mod = getModInstance();
  assert(mod && "Mod instance is null");
  
  // Provide the API set to the mod
  mod->LoadEFMod(&EFModLoaderAPI::GetEFModLoader());
  
  // Store the mod instance
  loadedMods[mod->GetIdentifier()] = mod;
  
  // Automatically register extended functions
  mod->RegisterAPIs();
  mod->RegisterHooks();
  
  RegisterApi::Register(); // Register APIs
  ...
  ```
  
  * Indeed, it's that simple. There isn't a complex implementation; this is from the official EFModLoader code.
  
  ### EFMod Implementation
  
  ```C++
  class EFMod {
  public:
      virtual ~EFMod() {}
  
      // Get the unique identifier of the mod
      virtual const char* GetIdentifier() const = 0;
  
      // Called when initializing the mod
      virtual bool Initialize() = 0;
  
      // Register locations the mod wants to hook and the function pointers after hooking
      virtual void RegisterHooks() = 0;
  
      // Register APIs
      virtual void RegisterAPIs() = 0;
  
      // Receive the API set provided by the loader
      virtual void LoadEFMod(EFModLoaderAPI* api) = 0;
  };
  ```
  
  * Your mod just needs to inherit from this class.
  
  ## [Developer Documentation](document/en/README.md)

