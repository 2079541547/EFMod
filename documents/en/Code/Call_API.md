## Getting a Field

```Cpp
EFModAPI::GetField<int /* Field type */>(
    {
        "A" /* Namespace */,
        "Class" /* Class */,
        "API" /* Field name */
    }); // Retrieve a field provided by the loader
```

## Calling a Function

```Cpp
EFModAPI::callFunction<int /* Function return type */>(
    {
        "A" /* Namespace */,
        "Class" /* Class */,
        "Func" /* Function name */,
        "int" /* Return type */,
        1 /* Number of parameters */
    },
    "Assume this is a string parameter, but it can be of any actual type" /* Parameter 1 */,
    ...
    ); // Call a function provided by the loader
```