## EFMod Directory Structure

```Text
Docs/
│
├── mod.json                    # Mod configuration
├── icon                            # Mod icon (png, jpg, webp, ...)
├── lib/                              # Mod executable files
│   ├── arm64-v8a/            # Directory for arm64 architecture executables
│   ├── armeabi-v7a/          # Directory for arm32 architecture executables
│   ├── x86_64/               # Directory for x86-64 architecture executables
│   └── x86/                  # Directory for x86-32 architecture executables
└── private/                  # Mod private directory
```

## Mod Configuration

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

An integer value that represents the current development standard of the Mod.

#### ModX

A boolean value indicating whether this mod is a standalone Mod. `false` means that this mod is not a standalone one.

#### name

A string representing the name of the mod. In this example, the mod name is "MyMod".

#### author

A string identifying the creator of this mod by their name or GitHub username. In this instance, the author is "EternalFuture".

#### version

A string representing the version number of the mod. It follows Semantic Versioning (SemVer) guidelines, and the current version is `1.0.0`.

#### github

An object containing information about the mod's GitHub project.

- **open source**: A boolean value indicating whether the project is open-source. `true` indicates that the project is open-source.
- **overview**: A string providing a link to the GitHub user's homepage rather than a specific repository link. The link points to the GitHub page of user [2079541547 (EternalFuture)](https://github.com/2079541547).
- **url**: A string that should contain the URL of the specific GitHub repository. Currently empty, which means no specific repository address has been provided yet.

#### Introduce

An object containing introduction texts in multiple languages to describe the functionality and features of the mod. Each language corresponds to a key-value pair, but all language introductions are currently empty. It's recommended to fill in the introductions for the following languages based on actual content:

- zh-cn: Simplified Chinese
- zh-hant: Traditional Chinese
- ru: Russian
- en: English
- ja: Japanese
- ko: Korean
- it: Italian
- es: Spanish
- fr: French
- de: German