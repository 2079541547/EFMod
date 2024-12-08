## EFMod 目录结构

```Text
Docs/
│
├── mod.json                    # Mod 配置
├── icon                            # Mod 图标(png, jpg, webp, ...)
├── lib/                              # Mod 可执行文件
│   ├── arm64-v8a/            # arm64架构的可执行文件目录
│   ├── armeabi-v7a/          # arm32架构的可执行文件目录
│   ├── x86_64/       # x86-64架构的可执行文件目录
│   └── x86/  # x86-32架构的可执行文件目录
└── private/  #Mod 私有目录
```

## Mod 配置

```json
{
    "standard": 20241208,
    "ModX": false,
    "name": "MyMod",
    "author": "EternalFuture",
    "version": "1.0.0",
    "github": {
        "open source": true,
        "overview": "https://github.com/2079541547",
        "url": ""
    },
    "Introduce": {
        "zh-cn": "",
        "zh-hant": "",
        "ru": "",
        "en": "",
        "ja": "",
        "ko": "",
        "it": "",
        "es": "",
        "fr": "",
        "de": ""
    }
}
```

### standard

整数值，表示当前Mod的开发标准

#### ModX

布尔值，表明该模组是否为独立Mod。`false` 表示该模组不是独立Mod。

#### name

字符串，代表模组的名称。在这个例子中，模组名为 "MyMod"。

#### author

字符串，标识创建此模组的作者姓名或GitHub用户名。在此实例中，作者为 "EternalFuture"。

#### version

字符串，表示模组的版本号。遵循语义化版本控制（SemVer）规范，当前版本为 `1.0.0`。

#### github

对象，包含有关模组GitHub项目的信息。

- **open source**：布尔值，指示该项目是否开源。`true` 表示该项目是开源的。
- **overview**：字符串，提供GitHub用户的主页链接，而不是特定的仓库链接。链接指向的是用户 [2079541547 (EternalFuture)](https://github.com/2079541547) 的GitHub页面。
- **url**：字符串，应包含具体GitHub仓库的URL。当前为空，意味着还没有提供具体的仓库地址。

#### Introduce

对象，包含了多种语言的模组介绍文本，用于描述模组的功能和特性。每种语言对应一个键值对，但目前所有语言的介绍都是空的。建议根据实际内容填充以下语言的介绍：

- zh-cn: 简体中文
- zh-hant: 繁体中文
- ru: 俄语
- en: 英语
- ja: 日语
- ko: 韩语
- it: 意大利语
- es: 西班牙语
- fr: 法语
- de: 德语
