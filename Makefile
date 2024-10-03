# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target executable (with .exe extension)
TARGET = blackjack.exe

# Source and object files
SRCS = driver.cpp game.cpp player.cpp deck.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target: build the program
all: $(TARGET)

# Rule to link object files into the .exe
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
