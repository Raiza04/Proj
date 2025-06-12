# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Target and source files
TARGET := main
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean run