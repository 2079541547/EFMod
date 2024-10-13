### 目录结构

假设我们的工作目录为 `example`，并且我们希望在这个目录下创建 `MyMod` 模组，其目录结构如下：

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
│   │   └── index.html  # 用户界面的HTML文件
│   ├── Private/
│   │   └── private_data.txt  # 私有数据文件
│   ├── icon.png  # 模组的图标
│   ├── info.json  # 模组的信息文件
│   ├── include/  # 包含头文件(编译时不计算)
│   │   ├── EFMod.hpp  # 模组基类头文件
│   │   └── EFModLoaderAPI.hpp  # 加载器API头文件
│   ├── src/  # 源代码目录(编译时不计算)
│   │   └── main.cpp  # 模组主文件
│   └── CMakeLists.txt  # 构建脚本(编译时不计算)
```

### 固定头文件

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

    // 获取模组的唯一标识符
    virtual const char* GetIdentifier() const = 0;

    // 模组初始化时调用
    virtual bool Initialize() = 0;

    // 注册模组要hook的位置和hook后的函数指针
    virtual void RegisterHooks() = 0;

    // 注册API
    virtual void RegisterAPIs() = 0;

    // 接收加载器提供的API集合
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
    // 注册模组的扩展函数
    void RegisterExtension(const std::string& extensionPoint, uintptr_t hook);

    // 注册API（被Mod调用）
    void RegisterAPI(const std::string& APIPoint, uintptr_t Api);

    // 查找扩展函数集合
    std::vector<uintptr_t> FindHooks(const std::string& extensionPoint);

    // 查找API集合
    std::vector<uintptr_t> FindAPIS(const std::string& APIPoint);

    // 获取单例实例
    static EFModLoaderAPI& GetEFModLoader();

private:
    // 用于存储扩展函数指针集合
    std::map<std::string, std::vector<uintptr_t>> extensions;
    std::mutex extensionsMutex;

    // 用于存储注册的API列表用于重定向
    std::map<std::string, std::vector<uintptr_t>> APIS;
    std::mutex APISMutex;

    // 私有构造函数
    EFModLoaderAPI() {}
};

// 实现单例的获取方法
inline EFModLoaderAPI& EFModLoaderAPI::GetEFModLoader() {
    static EFModLoaderAPI instance;
    return instance;
}

// 实现 RegisterExtension 方法
inline void EFModLoaderAPI::RegisterExtension(const std::string& extensionPoint, uintptr_t hook) {
    std::lock_guard<std::mutex> lock(extensionsMutex);
    extensions[extensionPoint].push_back(hook);
}

// 实现 RegisterAPI 方法
inline void EFModLoaderAPI::RegisterAPI(const std::string &APIPoint, uintptr_t Api) {
    std::lock_guard<std::mutex> lock(APISMutex);
    APIS[APIPoint].push_back(Api);
}

// 实现 FindHooks 方法
inline std::vector<uintptr_t> EFModLoaderAPI::FindHooks(const std::string& extensionPoint) {
    std::lock_guard<std::mutex> lock(extensionsMutex);
    auto it = extensions.find(extensionPoint);
    if (it == extensions.end()) {
        return {};
    }
    return it->second;
}

// 实现 FindAPIS 方法
inline std::vector<uintptr_t> EFModLoaderAPI::FindAPIS(const std::string& APIPoint) {
    std::lock_guard<std::mutex> lock(APISMutex);
    auto it = APIS.find(APIPoint);
    if (it == APIS.end()) {
        return {};
    }
    return it->second;
}
```

### 示例Mod源码

#### `src/main.cpp`

```cpp
//
// Created by example_author on 2024/10/13.
//
#include <iostream>
#include <vector>
#include <string>
#include <android/log.h>
#include "../include/EFMod.hpp" // 导入EFMod头文件
#include "../include/EFModLoaderAPI.hpp" // 导入EFModLoaderAPI头文件

// 定义模组类
class ExampleMod : public EFMod {
public:
    // 获取模组的唯一标识符
    const char* GetIdentifier() const override {
        return "ExampleMod"; // 返回模组的唯一标识符
    }

    // 模组初始化时调用
    bool Initialize() override {
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Initializing mod: %s", GetIdentifier());
        return true; // 初始化成功返回true
    }

    // 注册模组要hook的位置和hook后的函数指针
    void RegisterHooks() override {
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Registering hooks for mod: %s", GetIdentifier());

        // 注册Hook点
        std::vector<std::pair<std::string, uintptr_t>> hooks{
            {"Assembly-CSharp.dll.Terraria.Main.DamageVar", reinterpret_cast<uintptr_t>(&ModifyDamage)} // 注册Hook函数
        };

        // 遍历并注册hook
        for (const auto& [hookPoint, funcPtr] : hooks) {
            modAPI->RegisterExtension(hookPoint, funcPtr); // 使用Loader提供的API注册Hook
        }
    }

    // 注册API
    void RegisterAPIs() override {
        // 注册API（如果有需要的话）
        modAPI->RegisterAPI("ExampleAPI", reinterpret_cast<uintptr_t>(&ExampleAPI));
    }

    // 接收加载器提供的API集合
    void LoadEFMod(EFModLoaderAPI* api) override {
        // 保存Mod信息
        modAPI = api; // 保存加载器提供的API实例
    }

private:
    EFModLoaderAPI* modAPI = nullptr; // 保存EFModLoaderAPI的指针

    // 示例扩展函数
    void ModifyDamage() {
        // 实现修改伤害的逻辑
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Modifying damage...");
    }

    // 示例API函数
    void ExampleAPI() {
        // 实现API的逻辑
        __android_log_print(ANDROID_LOG_INFO, "ExampleMod", "Example API called...");
    }
};

// 导出模组实例
extern "C" EFMod* GetModInstance() {
    static ExampleMod modInstance; // 创建静态模组实例
    return &modInstance; // 返回模组实例的地址
}
```

### 构建脚本

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

### `info.json` 文件

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
  "Introduce": "这是一个示例Mod",
  "Version": "1.0.0"
}
```

### 目录解释

1. **`MyMod/`**
   
   - 模组的根目录，包含了所有模组相关的文件。
2. **`MyMod/Executable/`**
   
   - 这个目录包含了模组的不同架构版本的可执行文件或动态库。
   - 每个子目录对应不同的CPU架构：
     - **`arm64-v8a/`**: ARM64架构下的库文件。
     - **`armeabi-v7a/`**: ARMv7架构下的库文件。
     - **`x86/`**: x86架构下的库文件。
     - **`x86_64/`**: x86_64架构下的库文件。
3. **`MyMod/Page/`**
   
   - 这个目录包含了用户界面的相关文件，如HTML、CSS和JavaScript等。
   - 例如：`index.html` 可能是模组的设置页面。
4. **`MyMod/Private/`**
   
   - 这个目录存放的是模组的私有数据，这些数据只对模组本身可见。
   - 例如：`private_data.txt` 可能存储了一些只有该模组需要访问的数据。
5. **`MyMod/icon.png`**
   
   - 模组的图标文件，用于在模组管理器中识别模组。
6. **`MyMod/info.json`**
   
   - 模组的信息文件，包含模组的元数据，如名称、版本、作者等信息。
7. **`MyMod/include/`**
   
   - 包含头文件目录，包含了 `EFMod.hpp` 和 `EFModLoaderAPI.hpp`。
8. **`MyMod/src/`**
   
   - 源代码目录，包含了模组的源代码文件。
9. **`MyMod/CMakeLists.txt`**
   
   - 构建脚本，用于编译模组生成动态库文件。

通过以上步骤，您可以创建一个完整的模组，并且了解其目录结构和文件内容。这将有助于您更好地管理和开发模组。

