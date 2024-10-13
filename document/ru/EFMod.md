### Структура каталога

Предположим, что наш рабочий каталог является `example`, и мы хотим создать мод `MyMod` в этом каталоге. Структура каталогов будет следующей:

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
│   │   └── index.html  # Файл HTML пользовательского интерфейса
│   ├── Private/
│   │   └── private_data.txt  # Файл с приватными данными мода
│   ├── icon.png  # Иконка мода
│   ├── info.json  # Файл информации о моде
│   ├── include/  # Каталог с заголовочными файлами (не участвуют в компиляции)
│   │   ├── EFMod.hpp  # Заголовочный файл базового класса мода
│   │   └── EFModLoaderAPI.hpp  # Заголовочный файл API загрузчика
│   ├── src/  # Каталог исходного кода (не участвует в компиляции)
│   │   └── main.cpp  # Главный файл мода
│   └── CMakeLists.txt  # Скрипт сборки (не участвует в компиляции)
```

### Фиксированные заголовочные файлы

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

    // Получить уникальный идентификатор мода
    virtual const char* GetIdentifier() const = 0;

    // Вызывается при инициализации мода
    virtual bool Initialize() = 0;

    // Регистрирует функции, которые нужно перехватить и указатели на функции после перехвата
    virtual void RegisterHooks() = 0;

    // Регистрирует API
    virtual void RegisterAPIs() = 0;

    // Принимает набор API от загрузчика
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
    // Регистрирует расширение мода
    void RegisterExtension(const std::string& extensionPoint, uintptr_t hook);

    // Регистрирует API (используется модом)
    void RegisterAPI(const std::string& APIPoint, uintptr_t Api);

    // Находит наборы функций расширения
    std::vector<uintptr_t> FindHooks(const std::string& extensionPoint);

    // Находит наборы API
    std::vector<uintptr_t> FindAPIS(const std::string& APIPoint);

    // Получить экземпляр одиночки
    static EFModLoaderAPI& GetEFModLoader();

private:
    // Хранит наборы указателей на функции расширения
    std::map<std::string, std::vector<uintptr_t>> extensions;
    std::mutex extensionsMutex;

    // Хранит зарегистрированные API для перенаправления
    std::map<std::string, std::vector<uintptr_t>> APIS;
    std::mutex APISMutex;

    // Приватный конструктор
    EFModLoaderAPI() {}
};

// Реализация метода получения экземпляра одиночки
inline EFModLoaderAPI& EFModLoaderAPI::GetEFModLoader() {
    static EFModLoaderAPI instance;
    return instance;
}

// Реализация метода RegisterExtension
inline void EFModLoaderAPI::RegisterExtension(const std::string& extensionPoint, uintptr_t hook) {
    std::lock_guard<std::mutex> lock(extensionsMutex);
    extensions[extensionPoint].push_back(hook);
}

// Реализация метода RegisterAPI
inline void EFModLoaderAPI::RegisterAPI(const std::string &APIPoint, uintptr_t Api) {
    std::lock_guard<std::mutex> lock(APISMutex);
    APIS[APIPoint].push_back(Api);
}

// Реализация метода FindHooks
inline std::vector<uintptr_t> EFModLoaderAPI::FindHooks(const std::string& extensionPoint) {
    std::lock_guard<std::mutex> lock(extensionsMutex);
    auto it = extensions.find(extensionPoint);
    if (it == extensions.end()) {
        return {};
    }
    return it->second;
}

// Реализация метода FindAPIS
inline std::vector<uintptr_t> EFModLoaderAPI::FindAPIS(const std::string& APIPoint) {
    std::lock_guard<std::mutex> lock(APISMutex);
    auto it = APIS.find(APIPoint);
    if (it == APIS.end()) {
        return {};
    }
    return it->second;
}
```

### Пример исходного кода мода

#### `src/main.cpp`

```cpp
//
// Created by example_author on 2024/10/13.
//
#include <iostream>
#include <vector>
#include <string>
#include <android/log.h>
#include "../include/EFMod.hpp" // Включаем заголовочный файл EFMod
#include "../include/EFModLoaderAPI.hpp" // Включаем заголовочный файл EFModLoaderAPI

// Определение класса мода
class ExampleMod : public EFMod {
public:
    // Получить уникальный идентификатор мода
    const char* GetIdentifier() const override {
        return "ExampleMod"; // Возвращаем уникальный идентификатор мода
    }

    // Вызывается при инициализации мода
    bool Initialize() override {
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Инициализация мода: %s", GetIdentifier());
        return true; // Возвращает true при успешной инициализации
    }

    // Регистрирует функции, которые нужно перехватить и указатели на функции после перехвата
    void RegisterHooks() override {
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Регистрация хуков для мода: %s", GetIdentifier());

        // Регистрируем точки хука
        std::vector<std::pair<std::string, uintptr_t>> hooks{
            {"Assembly-CSharp.dll.Terraria.Main.DamageVar", reinterpret_cast<uintptr_t>(&ModifyDamage)} // Регистрируем функцию хука
        };

        // Проходимся по всем и регистрируем хуки
        for (const auto& [hookPoint, funcPtr] : hooks) {
            modAPI->RegisterExtension(hookPoint, funcPtr); // Регистрируем хук с использованием API загрузчика
        }
    }

    // Регистрирует API
    void RegisterAPIs() override {
        // Регистрирует API (если необходимо)
        modAPI->RegisterAPI("ExampleAPI", reinterpret_cast<uintptr_t>(&ExampleAPI));
    }

    // Принимает набор API от загрузчика
    void LoadEFMod(EFModLoaderAPI* api) override {
        // Сохраняем информацию мода
        modAPI = api; // Сохраняем экземпляр API загрузчика
    }

private:
    EFModLoaderAPI* modAPI = nullptr; // Сохраняет указатель на EFModLoaderAPI

    // Пример функции расширения
    void ModifyDamage() {
        // Реализация логики изменения урона
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Изменение урона...");
    }

    // Пример функции API
    void ExampleAPI() {
        // Реализация логики API
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Вызван пример API...");
    }
};

// Экспортирует экземпляр мода
extern "C" EFMod* GetModInstance() {
    static ExampleMod modInstance; // Создаем статический экземпляр мода
    return &modInstance; // Возвращаем адрес экземпляра мода
}
```

### Скрипт сборки

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

### Файл `info.json`

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
  "Introduce": "Это пример мода",
  "Version": "1.0.0"
}
```

### Объяснение каталогов

1. **`MyMod/`**

   - Корневой каталог мода, который содержит все файлы, связанные с модом.
2. **`MyMod/Executable/`**

   - Этот каталог содержит исполняемые файлы или динамические библиотеки мода для различных архитектур процессора.
   - Каждый подкаталог соответствует разным архитектурам CPU:
     - **`arm64-v8a/`**: Библиотека для архитектуры ARM64.
     - **`armeabi-v7a/`**: Библиотека для архитектуры ARMv7.
     - **`x86/`**: Библиотека для архитектуры x86.
     - **`x86_64/`**: Библиотека для архитектуры x86_64.
3. **`MyMod/Page/`**

   - Этот каталог содержит файлы пользовательского интерфейса, такие как HTML, CSS и JavaScript.
   - Например, `index.html` может быть страницей настроек мода.
4. **`MyMod/Private/`**

   - Этот каталог содержит приватные данные мода, которые видны только самому моду.
   - Например, `private_data.txt` может содержать данные, которые требуются только этому моду.
5. **`MyMod/icon.png`**

   - Файл иконки мода, используемый для идентификации мода в менеджере модов.
6. **`MyMod/info.json`**

   - Файл информации о моде, который содержит метаданные мода, такие как название, версию, автора и т.д.
7. **`MyMod/include/`**

   - Каталог заголовочных файлов, который содержит `EFMod.hpp` и `EFModLoaderAPI.hpp`.
8. **`MyMod/src/`**

   - Каталог исходного кода, который содержит файлы исходного кода мода.
9. **`MyMod/CMakeLists.txt`**

   - Скрипт сборки, используемый для компиляции мода и генерации динамической библиотеки.

С помощью вышеописанных шагов вы можете создать полный мод и понять его структуру каталогов и содержание файлов, что поможет вам лучше управлять и разрабатывать моды.
