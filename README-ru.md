# EFMod

* Эффективный, свободный и универсальный интрузивный мод

  ## Что может делать EFMod?

  * Всё, что вы можете себе представить!
  * Основное применение — создание модификаций для игр, таких как изменение игровых параметров   и добавление предметов.

  ## Как это работает?

  * EFModLoader — это загрузчик модов, который играет важную роль.
  * EFMod — сам мод, включая API.

  ## Принцип работы?

  * Через техники инъекции напрямую модифицирует игру, такие как технология Hook, затем загружает моды.
  * EFModLoader используется для загрузки модов, основные моды пишутся на C++, в них можно регистрировать API, существующие в EFModLoader, а также расширять игровые функции.

  ### Принцип загрузки

  ```C++
  ...
  // Получение экземпляра мода
  EFMod* (*getModInstance)();
  getModInstance = (EFMod* (*)())dlsym(handle, "GetModInstance");
  if (!getModInstance) {
      dlclose(handle);
      return;
  }

  EFMod* mod = getModInstance();
  assert(mod && "Mod instance is null");

  // Предоставление набора API моду
  mod->LoadEFMod(&EFModLoaderAPI::GetEFModLoader());

  // Хранение экземпляра мода
  loadedMods[mod->GetIdentifier()] = mod;

  // Автоматическая регистрация расширительных функций
  mod->RegisterAPIs();
  mod->RegisterHooks();

  RegisterApi::Register(); // Регистрация API

  ...
  ```

  * Да, всё так просто, без сложной реализации, это код из официального EFModLoader.

  ### Реализация EFMod

  ```C++
  class EFMod {
  public:
      virtual ~EFMod() {}

      // Получение уникального идентификатора мода
      virtual const char* GetIdentifier() const = 0;

      // Вызывается при инициализации мода
      virtual bool Initialize() = 0;

      // Регистрация мест, которые нужно hook'нуть, и указателей на функции после hook'а
      virtual void RegisterHooks() = 0;

      // Регистрация API
      virtual void RegisterAPIs() = 0;

      // Приём набора API от загрузчика
      virtual void LoadEFMod(EFModLoaderAPI* api) = 0;
  };
  ```

* Ваш мод должен наследовать этот класс.

## [Документация для разработчиков](document/ru/README.md)

