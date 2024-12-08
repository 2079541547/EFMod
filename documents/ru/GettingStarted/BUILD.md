## Формат файла Mod

* [SilkCasket](https://github.com/2079541547/SilkCasket)
  * Это гибкий и быстрый формат файла, который в большинстве случаев обеспечивает несколько лучшее сжатие по сравнению с zip и более безопасный.

## Шаги сборки

* Структура Mod должна следовать стандарту, описанному [здесь](EFMOD.md) (см. другие стандарты для подробностей).
* Рекомендуется собирать в Linux, убедитесь, что установлены clang и cmake.

### 1. Получение SilkCasket

```bash
>> git clone https://github.com/2079541547/SilkCasket.git
```

### 2. Сборка SilkCasket

```bash
>> cd SilkCasket
>> cmake CMakeLists.txt
>> make
```

### 3. Запуск example-tool

```
>> ./example-tool -h  # Выводит справку
>> ./example-tool -b <input_path> <output_path> <block_size> EFMod
```

### После завершения будет создан файл skc в указанном 'output_path'
