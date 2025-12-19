## @file Makefile
## @brief Makefile для сборки проекта шифрования методом маршрутной перестановки
## @details Содержит цели для сборки основной и альтернативной программ,
##          генерации документации и очистки проекта
## @version 1.0
## @date 2024

# Компилятор и флаги
CXX = g++                       ##< Компилятор C++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2  ##< Флаги компиляции: C++11, все предупреждения, оптимизация O2
TARGET = cipher                 ##< Имя основного исполняемого файла
ALT_TARGET = cipher_alt         ##< Имя альтернативного исполняемого файла

# Исходные файлы
SOURCES = modAlphaCipher.cpp main.cpp           ##< Исходные файлы для основной программы
ALT_SOURCES = modAlphaCipher.cpp main_alternative.cpp  ##< Исходные файлы для альтернативной программы

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)           ##< Объектные файлы основной программы
ALT_OBJECTS = $(ALT_SOURCES:.cpp=.o)   ##< Объектные файлы альтернативной программы

# Основная цель - сборка основной программы
## @brief Сборка основной программы шифрования
all: $(TARGET)

# Основная программа
## @brief Правило сборки основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Альтернативная программа
## @brief Сборка альтернативной версии программы
alt: $(ALT_TARGET)

## @brief Правило сборки альтернативной программы
$(ALT_TARGET): $(ALT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(ALT_TARGET) $(ALT_OBJECTS)

# Компиляция объектных файлов
## @brief Правило для компиляции .cpp файлов в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
## @brief Удаление всех скомпилированных файлов
clean:
	rm -f $(TARGET) $(ALT_TARGET) $(OBJECTS) $(ALT_OBJECTS)

# Запуск
## @brief Сборка и запуск основной программы
run: $(TARGET)
	./$(TARGET)

# Запуск альтернативной версии
## @brief Сборка и запуск альтернативной программы
run-alt: $(ALT_TARGET)
	./$(ALT_TARGET)

# Генерация документации Doxygen
## @brief Генерация HTML документации
doc-html:
	doxygen Doxyfile

## @brief Генерация PDF документации (требует установленного LaTeX)
doc-pdf:
	cd latex && make

## @brief Генерация всей документации
doc: doc-html doc-pdf

## @brief Очистка сгенерированной документации
clean-doc:
	rm -rf docs html latex

# Отладочная сборка
## @brief Сборка с отладочной информацией
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)

# Тестирование
## @brief Запуск тестов (если есть тестовая программа)
test: $(TARGET)
	@echo "Запуск тестов..."
	./$(TARGET) < test_input.txt

# Зависимости файлов
## @brief Зависимости для файлов
modAlphaCipher.o: modAlphaCipher.h
main.o: modAlphaCipher.h
main_alternative.o: modAlphaCipher.h

## @brief Помощь по доступным командам
help:
	@echo "Доступные команды:"
	@echo "  make all       - сборка основной программы (по умолчанию)"
	@echo "  make alt       - сборка альтернативной программы"
	@echo "  make clean     - удаление скомпилированных файлов"
	@echo "  make run       - сборка и запуск основной программы"
	@echo "  make run-alt   - сборка и запуск альтернативной программы"
	@echo "  make doc       - генерация документации Doxygen"
	@echo "  make doc-html  - генерация HTML документации"
	@echo "  make doc-pdf   - генерация PDF документации"
	@echo "  make clean-doc - очистка документации"
	@echo "  make debug     - отладочная сборка"
	@echo "  make test      - запуск тестов"
	@echo "  make help      - эта справка"

.PHONY: all alt clean run run-alt doc doc-html doc-pdf clean-doc debug test help
