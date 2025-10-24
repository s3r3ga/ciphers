# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = cipher
ALT_TARGET = cipher_alt

# Исходные файлы
SOURCES = modAlphaCipher.cpp main.cpp
ALT_SOURCES = modAlphaCipher.cpp main_alternative.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)
ALT_OBJECTS = $(ALT_SOURCES:.cpp=.o)

# Основная цель
all: $(TARGET)

# Основная программа
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Альтернативная программа
alt: $(ALT_TARGET)

$(ALT_TARGET): $(ALT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(ALT_TARGET) $(ALT_OBJECTS)

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET) $(ALT_TARGET) $(OBJECTS) $(ALT_OBJECTS)

# Запуск
run: $(TARGET)
	./$(TARGET)

# Запуск альтернативной версии
run-alt: $(ALT_TARGET)
	./$(ALT_TARGET)

# Зависимости
modAlphaCipher.o: modAlphaCipher.h
main.o: modAlphaCipher.h
main_alternative.o: modAlphaCipher.h

.PHONY: all clean run run-alt alt
