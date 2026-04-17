# Для добавления библиотеки, нужно выполнить следующие действия:
1. Создать папку `/lib/src/$(LIB_NAME)`
2. Добавить в неё Makefile следующего содержания:
```makefile
LIB_NAME = Название библиотеки
SRCS = Список .cpp исходников

include ../Template.mk
```

# Для подключения библиотеки нужно добавить в `/workspace/CMakeList.txt` в команду `target_link_libraries` название библиотеки.

# Чтобы использовать библиотеку в коде, достаточно написать `#inlude "$(LIB_NAME)/path/to/header/from/lib/root.h"`
