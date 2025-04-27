CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Source files
SRC = src/editor.cpp main.cpp

# Object files (replace .cpp with .o)
OBJ = $(SRC:.cpp=.o)

# Output executable
TARGET = editor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# How to build .o files from .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean run