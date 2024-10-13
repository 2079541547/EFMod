# EFMod

* [Русский язык](README-ru.md)
* [English](README-en.md)
* 一种高效自由通用的入侵式的Mod
  
  ## EFMod可以做什么？
  
  * 你能想象到的任何事！
  * 主要用于游戏Mod，如修改游戏数值以及添加物品
  
  ## 如何实现？
  
  * EFModLoader - 此为Mod加载器，较为重要
  * EFMod - Mod本体，包括API
  
  ## 原理？
  
  * 通过注入手段直接修改游戏，如Hook技术，然后进行Mod的加载
  * EFModLoader用于加载Mod，Mod主要为C++编写，可以在Mod中注册EFModLoader中存在的API以及对游戏函数进行扩展
    
    ## 加载原理
    
    ```C++
    ...
    
    // 获取模组实例
    EFMod* (*getModInstance)();
    getModInstance = (EFMod* (*)())dlsym(handle, "GetModInstance");
    if (!getModInstance) {
        dlclose(handle);
        return;
    }
    
    EFMod* mod = getModInstance();
    assert(mod && "Mod instance is null");
    
    // 提供API集合给模组
    mod->LoadEFMod(&EFModLoaderAPI::GetEFModLoader());
    
    // 存储模组实例
    loadedMods[mod->GetIdentifier()] = mod;
    
    // 自动注册扩展函数
    mod->RegisterAPIs();
    mod->RegisterHooks();
    
    RegisterApi::Register(); //注册API
    
    ...
    ```
    
    * 没错，就这么简单，没有复杂的实现，此为官方EFModLoader中的代码
    
    ## EFMod实现
    
    ```C++
    class EFMod {
        public:
        virtual ~EFMod() {}
    
        // 获取模组的唯一标识符
        virtual const char* GetIdentifier() const = 0;
    
        // 模组初始化时调用
        virtual bool Initialize() = 0;
    
        // 注册模组要hook的位置和hook后的函数指针
        virtual void RegisterHooks() = 0;
    
        //注册API
        virtual void RegisterAPIs() = 0;
    
        // 接收加载器提供的API集合
        virtual void LoadEFMod(EFModLoaderAPI* api) = 0;
      };
    ```
    
    * 你的Mod只需要继承此类
  
  ## [开发者文档](document/zh/README.md)

