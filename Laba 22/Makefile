# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
LDFLAGS = 

# Целевые файлы
TARGET = cipher
SOURCES = main.cpp modAlphaCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = modAlphaCipher.h

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Компиляция main.cpp
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Компиляция modAlphaCipher.cpp
modAlphaCipher.o: modAlphaCipher.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp -o modAlphaCipher.o

# Очистка скомпилированных файлов
clean:
	rm -f $(OBJECTS) $(TARGET)

# Установка (если нужно)
install: $(TARGET)
	@echo "Установка в /usr/local/bin (требуются права root)"
	@# sudo cp $(TARGET) /usr/local/bin/

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Отладочная сборка
debug: CXXFLAGS += -g -DDEBUG
debug: rebuild

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all      - сборка программы (по умолчанию)"
	@echo "  clean    - удаление скомпилированных файлов"
	@echo "  run      - сборка и запуск программы"
	@echo "  debug    - сборка с отладочной информацией"
	@echo "  install  - установка программы (требуются права root)"
	@echo "  help     - показать эту справку"

.PHONY: all clean rebuild install run debug help
