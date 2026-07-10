# Линейные коллекции: поиск и сортировка (C и C++)

Учебные реализации линейного, бинарного и хеш-поиска, а также сортировок
над коллекцией целых чисел. Каждая задача написана дважды — на C17 и на
идиоматичном C++23, — чтобы видеть разницу подходов (ручная память и `errno`
против RAII, STL и `std::ranges`).

## Требования

- MSVC (Visual Studio Build Tools) с компонентом C++
- `vswhere` (входит в поставку Visual Studio Installer)
- сборка запускается из окружения «x64 Native Tools» (его настраивает
  `build.bat` через `vcvarsall.bat`)
- сборка только для Windows/MSVC; кроссплатформенный Makefile появится на слое 15

## Сборка

```bat
build.bat
```

Скрипт находит установку Visual Studio через `vswhere`, поднимает окружение
`x64` и собирает все цели раздельными этапами (`cl /c` → `link`).
Результат — исполняемые файлы рядом с исходниками:
`linear-collections\c_version\*.exe` и `linear-collections\cpp_version\*.exe`.

## Запуск

```bat
linear-collections\cpp_version\search_l1.exe
```

Пример вывода:

```text
Array: [5, 2, 8, 2, 9, 1, 2, 7, 3, 2]
Search key K = 9
Index of first occurrence: 4
Number of comparisons: 5
```

На текущем уровне (L1) данные и параметры зашиты в `main()` как константы;
чтение из потока и аргументы командной строки подключаются на следующих слоях.

## Структура

```text
linear-collections\
  c_version\      реализации на чистом C17
  cpp_version\    идиоматичный C++23
```

Уровни задачи (в именах файлов): `search_l1` — линейный поиск,
`sort_l2` — сортировка выбором/пузырьком, `search_l3` — бинарный поиск,
`sort_l4` — merge/quick/heap, `search_l5` — поиск через хеш-таблицу.

## start_env.bat

Открывает FAR Manager с настроенным окружением «x64 Native Tools»
для ручной сборки и отладки из консоли.
