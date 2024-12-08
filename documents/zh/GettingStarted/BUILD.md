## Mod文件格式

* [SilkCasket](https://github.com/2079541547/SilkCasket)
  * 这是一种灵活快速的文件格式，在大多数情况下压缩率略高于zip且更安全

## 构建步骤

* Mod结构请按照[这里](EFMOD.md)的标准(具体看其他标准)
* 推荐linux构建，确保已安装clang cmake

### 1. 拉取 SilkCasket

```bash
>> git clone https://github.com/2079541547/SilkCasket.git
```

### 2. 构建 SilkCasket

```bash
>> cd SilkCasket
>> cmake CMakeLists.txt
>> make
```

### 3. 运行 example-tool

```
>> ./example-tool -h  #打印帮助
>> ./example-tool -b <input_path> <output_path> <block_size> EFMod
```

### 完成后就会在 指定的'output_path'输出

