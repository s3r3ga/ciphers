# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = cipher
SOURCES = modAlphaCipher.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Основная цель
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Отладочная сборка
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Статическая сборка
static: CXXFLAGS += -static
static: $(TARGET)

# Очистка
clean:
	rm -f $(TARGET) $(OBJECTS) *.gch

# Установка (если нужно)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Тестирование
test: $(TARGET)
	./$(TARGET)

# Сборка всех версий
all: $(TARGET) debug static

# Зависимости
modAlphaCipher.o: modAlphaCipher.h
main.o: modAlphaCipher.h

.PHONY: all clean install test debug static
