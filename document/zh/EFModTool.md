### EFMod 工具使用指南

#### 介绍

EFModTool 是一个辅助工具，旨在简化 EFMod 模组的创建、管理和打包过程。通过命令行界面，您可以快速生成模组模板、管理模组文件等。

#### 命令选项

以下是 EFModTool 支持的命令及其用途：

##### `-cm <Output Path> <Mod Name> <Author> <Special Loading (true/false)> <Enable Private (true/false)> <Customize Page (true/false)> <Open Source (true/false)>`

**用途**: 创建一个EFMod模组模板。

**参数说明**:

- `<Output Path>`: 模组输出路径。
- `<Mod Name>`: 模组名称。
- `<Author>`: 模组作者。
- `<Special Loading (true/false)>`: 是否具有特殊的加载级别。
- `<Enable Private (true/false)>`: 是否启用模组的私有目录。
- `<Customize Page (true/false)>`: 是否允许自定义模组页面。
- `<Open Source (true/false)>`: 是否开源。

**示例**:

```bash
./EFModTool_x86-64 -cm /path/to/output MyMod ExampleAuthor false true false true
```

##### `-cefm <Output Path> <Mod Name> <Author>`

**用途**: 创建一个空的EFMod模组。

**参数说明**:

- `<Output Path>`: 模组输出路径。
- `<Mod Name>`: 模组名称。
- `<Author>`: 模组作者。

**示例**:

```bash
./EFModTool_x86-64 -cefm /path/to/output EmptyMod ExampleAuthor
```

##### `-cefl <Output Path> <Loader Name> <Author>`

**用途**: 创建一个EFModLoader实例。

**参数说明**:

- `<Output Path>`: Loader 输出路径。
- `<Loader Name>`: Loader 名称。
- `<Author>`: Loader 作者。

**示例**:

```bash
./EFModTool_x86-64 -cefl /path/to/output NewLoader ExampleAuthor
```

##### `-rm <Mod Path>`

**用途**: 移除一个EFMod模组。

**参数说明**:

- `<Mod Path>`: 模组路径。

**示例**:

```bash
./EFModTool_x86-64 -rm /path/to/mod
```

##### `-efmc <Window maximum value> <Source Dir> <Target Dir> <Output Path>`

**用途**: 执行模组的构建操作。

**参数说明**:

- `<Window maximum value>`: 窗口最大值（压缩最佳值上限）。
- `<Source Dir>`: 源目录。
- `<Target Dir>`: 目标目录。
- `<Output Path>`: 构建输出路径。

**示例**:

```bash
./EFModTool_x86-64 -efmc 1024 /path/to/source /path/to/target /path/to/output
```

##### `-efml <Window maximum value> <Source Dir> <Target Dir> <Output Path>`

**用途**: 执行Loader的构建操作。

**参数说明**:

- `<Window maximum value>`: 窗口最大值（压缩最佳值上限）。
- `<Source Dir>`: 源目录。
- `<Target Dir>`: 目标目录。
- `<Output Path>`: 构建输出路径。

**示例**:

```bash
./EFModTool_x86-64 -efml 1024 /path/to/source /path/to/target /path/to/output
```

##### `-h`

**用途**: 显示帮助信息。

**示例**:

```bash
./EFModTool_x86-64 -h
```

#### 总结

通过上述命令，您可以轻松地管理您的EFMod模组。无论是创建新的模组还是构建已有的模组，EFModTool 都能为您提供便捷的帮助。如果您有任何疑问或需要进一步的帮助，请参考工具的详细文档或联系技术支持。
