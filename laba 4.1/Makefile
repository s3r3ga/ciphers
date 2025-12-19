## @file Makefile
## @brief Makefile для сборки проекта шифрования Гронсвельда
## @details Содержит цели для сборки, отладки, тестирования и генерации документации

# Компилятор и флаги
CXX = g++ ##< Компилятор C++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 ##< Флаги компиляции
TARGET = cipher ##< Имя исполняемого файла
SOURCES = modAlphaCipher.cpp main.cpp ##< Исходные файлы
OBJECTS = $(SOURCES:.cpp=.o) ##< Объектные файлы

# Основная цель
## @brief Сборка основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция объектных файлов
## @brief Правило для компиляции .cpp файлов в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Отладочная сборка
## @brief Сборка с отладочной информацией
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Статическая сборка
## @brief Статическая линковка
static: CXXFLAGS += -static
static: $(TARGET)

# Очистка
## @brief Удаление скомпилированных файлов
clean:
	rm -f $(TARGET) $(OBJECTS) *.gch

# Установка
## @brief Установка программы в систему
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Тестирование
## @brief Запуск тестовой программы
test: $(TARGET)
	./$(TARGET)

# Генерация документации Doxygen
## @brief Генерация HTML документации
doc-html:
	doxygen Doxyfile

## @brief Генерация PDF документации
doc-pdf:
	cd latex && make

## @brief Генерация всей документации
doc: doc-html doc-pdf

## @brief Очистка документации
clean-doc:
	rm -rf docs html latex

# Сборка всех версий
## @brief Сборка всех вариантов программы
all: $(TARGET) debug static

# Зависимости
modAlphaCipher.o: modAlphaCipher.h
main.o: modAlphaCipher.h

.PHONY: all clean install test debug static doc doc-html doc-pdf clean-doc
