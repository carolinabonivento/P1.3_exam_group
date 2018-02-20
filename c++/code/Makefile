# -*- Makefile -*-
CXX = c++
CXXFLAGS = -g -std=c++11 -Wall -Wextra #-O3
LDLIBS= -lm

default: binary_tree.x

clean:
	rm -f *~ *# *.x *.o *.out

# Linker rule
binary_tree.x: binary_tree.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDLIBS)

# Compilation pattern rule for objects
%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Run the executable
check: binary_tree.x

# Valgrind to check eventual memory leaks
valgrind: binary_tree.x
	valgrind ./binary_tree.x

# Legend
# $@ => the executable written up
# $^ => ????
# $< => file.cc becomes file.x
