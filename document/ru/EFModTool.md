### Руководство по использованию инструмента EFModTool

#### Введение

EFModTool — это вспомогательный инструмент, предназначенный для упрощения создания, управления и упаковки модификаций (модов) для EFMod. С помощью командной строки вы можете быстро создавать шаблоны модов, управлять файлами модов и так далее.

#### Командные опции

Вот список поддерживаемых команд EFModTool и их назначение:

##### `-cm <Output Path> <Mod Name> <Author> <Special Loading (true/false)> <Enable Private (true/false)> <Customize Page (true/false)> <Open Source (true/false)>`

**Назначение**: Создание шаблона мода EFMod.

**Описание параметров**:

- `<Output Path>`: Путь для вывода мода.
- `<Mod Name>`: Имя мода.
- `<Author>`: Автор мода.
- `<Special Loading (true/false)>`: Имеет ли мод специальный уровень загрузки.
- `<Enable Private (true/false)>`: Включает ли мод приватный каталог.
- `<Customize Page (true/false)>`: Разрешает ли мод кастомизацию страницы.
- `<Open Source (true/false)>`: Открытый ли код мода.

**Пример**:

```bash
./EFModTool_x86-64 -cm /path/to/output MyMod ExampleAuthor false true false true
```

##### `-cefm <Output Path> <Mod Name> <Author>`

**Назначение**: Создание пустого мода EFMod.

**Описание параметров**:

- `<Output Path>`: Путь для вывода мода.
- `<Mod Name>`: Имя мода.
- `<Author>`: Автор мода.

**Пример**:

```bash
./EFModTool_x86-64 -cefm /path/to/output EmptyMod ExampleAuthor
```

##### `-cefl <Output Path> <Loader Name> <Author>`

**Назначение**: Создание экземпляра EFModLoader.

**Описание параметров**:

- `<Output Path>`: Путь для вывода загрузчика.
- `<Loader Name>`: Имя загрузчика.
- `<Author>`: Автор загрузчика.

**Пример**:

```bash
./EFModTool_x86-64 -cefl /path/to/output NewLoader ExampleAuthor
```

##### `-rm <Mod Path>`

**Назначение**: Удаление мода EFMod.

**Описание параметров**:

- `<Mod Path>`: Путь до мода.

**Пример**:

```bash
./EFModTool_x86-64 -rm /path/to/mod
```

##### `-efmc <Window maximum value> <Source Dir> <Target Dir> <Output Path>`

**Назначение**: Выполнение сборки мода.

**Описание параметров**:

- `<Window maximum value>`: Максимальное значение окна (верхний предел для наилучшего сжатия).
- `<Source Dir>`: Исходная директория.
- `<Target Dir>`: Целевая директория.
- `<Output Path>`: Путь для вывода сборки.

**Пример**:

```bash
./EFModTool_x86-64 -efmc 1024 /path/to/source /path/to/target /path/to/output
```

##### `-efml <Window maximum value> <Source Dir> <Target Dir> <Output Path>`

**Назначение**: Выполнение сборки загрузчика.

**Описание параметров**:

- `<Window maximum value>`: Максимальное значение окна (верхний предел для наилучшего сжатия).
- `<Source Dir>`: Исходная директория.
- `<Target Dir>`: Целевая директория.
- `<Output Path>`: Путь для вывода сборки.

**Пример**:

```bash
./EFModTool_x86-64 -efml 1024 /path/to/source /path/to/target /path/to/output
```

##### `-h`

**Назначение**: Показывает информацию о помощи.

**Пример**:

```bash
./EFModTool_x86-64 -h
```

#### Заключение

С помощью вышеуказанных команд вы можете легко управлять своими модификациями EFMod. Будь то создание нового мода или сборка существующего мода, EFModTool обеспечивает удобство и простоту использования. Если у вас есть вопросы или вам требуется дополнительная помощь, обратитесь к подробной документации инструмента или свяжитесь со службой технической поддержки.
