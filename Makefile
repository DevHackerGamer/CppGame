# #This is a comment
# INC="./inc"
# FLAGS=-I$(INC)
# CFLAGS = -g -Wall
# CC=gcc
# CPP=g++
	
# #SOURCES=$(wildcard *.c)
# OBJECTS=$(patsubst %.c, %, $(wildcard *.c)) $(patsubst %.cpp, %, $(wildcard *.cpp))


# all: $(OBJECTS)
# 	@echo 'objects are "$(OBJECTS)"'

# %: %.c
# 	$(CC) $(CFLAGS) $(OMPFLAGS) $< -o $@

# %: %.cpp
# 	$(CPP) $(CFLAGS) $(OMPFLAGS) $< -o $@
	
# clean:
# 	rm -vf $(OBJECTS)



# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Target executable
TARGET = CppGame

# Source files
SRCS = main.cpp Objects.cpp

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