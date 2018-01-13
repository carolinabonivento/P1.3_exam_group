SRC = $(wildcard *.cc)
CXX = c++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -I ../../lectures/04_error_handling
# used only by the script: 4_simple_vector_implemented_as.cc
EXE = $(SRC:.cc=.x)
INC = $(wildcard *.h)

.SUFFIXES:
.SUFFIXES: .cc .x

all: $(EXE)

%.x: %.cc 
	$(CXX) $< -o $@ $(CXXFLAGS)

format: $(SRC) $(INC)
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	rm -f $(EXE) *~ *# *.x *.out

.PHONY: clean


//First Modify Aurora
