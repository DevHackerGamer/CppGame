# Makefile for C++ game project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Target executable
TARGET = CppGame

# Source files
SRCS = main.cpp Objects.cpp algs.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)