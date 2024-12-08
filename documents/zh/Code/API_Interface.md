## 引入头文件

* [头文件](../../../include)

```C++
#include "EFMod.hpp" //引入此文件即可
```

## 实现 Mod 接口

* 标准 Mod

```Cpp
std::map<uint64_t, std::vector<void *>> get_hooks()
{
    /**
     * 做你想做的，如注册 hook
     */
    EFMod::registerHook(
        {
            "A" /* 命名空间 */,
            "Class" /* 类 */,
            "Func" /* 函数名称 */,
            "int" /* 返回值 */,
            1 /* 参数数量 */
        } /* hook的方法信息 */,
        (void *)MyFun    /* hook后插入逻辑，注: MyFun是一个函数，请保证插入的函数也是相同参数并使用(void *)进行类型转换，否则可能会导致崩溃 */
    );                   // 对在A命名空间中的Class类中为int类型传入1个参数的Func方法
    return EFMod::hooks; // 返回 hook 表
} // 这个函数实现是必不可少的，即使只返回一个空的map，优先级在API之后初始化之前

void CreateMod()
{
    /**
     * Mod 加载成功执行的逻辑，如使用API获取私有目录
     */
    EFMod::initialization(); // 调用初始化函数，如果需要
}

bool EFMod::initialization()
{
    /**
     * Mod 初始化函数
     */
    return true;
}
```

* 独立Mod

```Cpp
/**
* 注意：
能力越大，责任越大！！！！
能力越大，责任越大！！！！
能力越大，责任越大！！！！

独立 Mod 吃不到加载器提供的API，但是没有任何限制，这是极度危险的！！！
*/
// 如果是安卓平台
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved)
{
    JNIEnv *env;
    vm->GetEnv((void **)&env, JNI_VERSION_1_6);

    /*
     * 做任何你想做的
     */

    return JNI_VERSION_1_6;
}

// 其他平台
int OnLoad()
{
    /*
     * 做任何你想做的
     */

    return 0;
}
```

