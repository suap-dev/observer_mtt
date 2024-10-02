# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I/usr/include/lua5.3

# Linker flags (for Lua)
LDFLAGS = -llua5.3

# Source files
SRC = src/main.cpp  # Only compile the cpp files, headers are automatically included

# Output binary
TARGET = event_system

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean target
clean:
	rm -f $(TARGET)
