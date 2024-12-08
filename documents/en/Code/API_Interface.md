## Include Header Files

* [Header File](../../../include)

```C++
#include "EFMod.hpp" // Including this file is sufficient
```

## Implementing the Mod Interface

### Standard Mod

```Cpp
std::map<uint64_t, std::vector<void *>> get_hooks()
{
    /**
     * Do what you need to do, such as registering hooks
     */
    EFMod::registerHook(
        {
            "A", /* Namespace */
            "Class", /* Class */
            "Func", /* Function name */
            "int", /* Return type */
            1 /* Number of parameters */
        } /* Information about the method to hook */,
        (void *)MyFun /* The logic to insert after the hook; note: MyFun is a function. Ensure that the inserted function has the same parameters and use (void *) for type conversion, or it may cause a crash */
    );                   // Hooking a method named Func in class Class within namespace A which returns an int and takes 1 parameter
    return EFMod::hooks; // Return the hook table
} // This function implementation is essential, even if it only returns an empty map, its priority is between API initialization and before the actual initialization

void CreateMod()
{
    /**
     * Logic to execute upon successful Mod loading, such as using APIs to obtain a private directory
     */
    EFMod::initialization(); // Call the initialization function if necessary
}

bool EFMod::initialization()
{
    /**
     * Mod initialization function
     */
    return true;
}
```

### Standalone Mod

```Cpp
/**
* WARNING:
With great power comes great responsibility!!!!!
With great power comes great responsibility!!!!!
With great power comes great responsibility!!!!! 

Standalone Mods do not have access to loader-provided APIs but have no restrictions, which can be extremely dangerous!!!
*/
// If on the Android platform
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved)
{
    JNIEnv *env;
    vm->GetEnv((void **)&env, JNI_VERSION_1_6);

    /*
     * Do whatever you need to do
     */

    return JNI_VERSION_1_6;
}

// For other platforms
int OnLoad()
{
    /*
     * Do whatever you need to do
     */

    return 0;
}
```