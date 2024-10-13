### EFMod Tool Usage Guide

#### Introduction

EFModTool is an auxiliary tool designed to simplify the creation, management, and packaging process of EFMod mods. Through a command-line interface, you can quickly generate mod templates, manage mod files, and more.

#### Command Options

Below are the commands supported by EFModTool along with their purposes:

##### `-cm <Output Path> <Mod Name> <Author> <Special Loading (true/false)> <Enable Private (true/false)> <Customize Page (true/false)> <Open Source (true/false)>`

**Purpose**: Creates an EFMod mod template.

**Parameter Description**:

- `<Output Path>`: Output path for the mod.
- `<Mod Name>`: Name of the mod.
- `<Author>`: Author of the mod.
- `<Special Loading (true/false)>`: Whether the mod has special loading priority.
- `<Enable Private (true/false)>`: Whether to enable the mod's private directory.
- `<Customize Page (true/false)>`: Whether to allow customization of the mod page.
- `<Open Source (true/false)>`: Whether the mod is open-source.

**Example**:

```bash
./EFModTool_x86-64 -cm /path/to/output MyMod ExampleAuthor false true false true
```

##### `-cefm <Output Path> <Mod Name> <Author>`

**Purpose**: Creates an empty EFMod mod.

**Parameter Description**:

- `<Output Path>`: Output path for the mod.
- `<Mod Name>`: Name of the mod.
- `<Author>`: Author of the mod.

**Example**:

```bash
./EFModTool_x86-64 -cefm /path/to/output EmptyMod ExampleAuthor
```

##### `-cefl <Output Path> <Loader Name> <Author>`

**Purpose**: Creates an EFModLoader instance.

**Parameter Description**:

- `<Output Path>`: Output path for the loader.
- `<Loader Name>`: Name of the loader.
- `<Author>`: Author of the loader.

**Example**:

```bash
./EFModTool_x86-64 -cefl /path/to/output NewLoader ExampleAuthor
```

##### `-rm <Mod Path>`

**Purpose**: Removes an EFMod mod.

**Parameter Description**:

- `<Mod Path>`: Path to the mod.

**Example**:

```bash
./EFModTool_x86-64 -rm /path/to/mod
```

##### `-efmc <Window maximum value> <Source Dir> <Target Dir> <Output Path>`

**Purpose**: Performs the build operation for a mod.

**Parameter Description**:

- `<Window maximum value>`: Maximum window value (upper limit for optimal compression).
- `<Source Dir>`: Source directory.
- `<Target Dir>`: Target directory.
- `<Output Path>`: Output path for the build.

**Example**:

```bash
./EFModTool_x86-64 -efmc 1024 /path/to/source /path/to/target /path/to/output
```

##### `-efml <Window maximum value> <Source Dir> <Target Dir> <Output Path>`

**Purpose**: Performs the build operation for a loader.

**Parameter Description**:

- `<Window maximum value>`: Maximum window value (upper limit for optimal compression).
- `<Source Dir>`: Source directory.
- `<Target Dir>`: Target directory.
- `<Output Path>`: Output path for the build.

**Example**:

```bash
./EFModTool_x86-64 -efml 1024 /path/to/source /path/to/target /path/to/output
```

##### `-h`

**Purpose**: Displays help information.

**Example**:

```bash
./EFModTool_x86-64 -h
```

#### Summary

With the above commands, you can easily manage your EFMod mods. Whether creating new mods or building existing ones, EFModTool provides convenient assistance. If you have any questions or need further help, please refer to the detailed documentation of the tool or contact technical support.

