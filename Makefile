# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++14 -Wall
# Executable name
TARGET := PageRank
# Source files
SRCS := main.cpp graph.cpp pageRank.cpp
# Object files (automatically generated)
OBJS := $(SRCS:.cpp=.o)
# Header files directory
INCLUDES := -I.

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets
.PHONY: clean
