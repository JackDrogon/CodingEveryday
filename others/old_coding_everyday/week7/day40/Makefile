CXX := g++
# CXXFLAGS := -lleveldb
CPP := $(CXX) -E

OBJ := leveldb.o
SRC := leveldb.cc leveldb.h
EXAMPLE_SRC := leveldb_test.cc

.PHONY: all clean

all: $(OBJ)

$(OBJ): $(SRC)

example: $(OBJ) $(EXAMPLE_SRC)
	$(CXX) -lleveldb $^ -o example

clean:
	-$(RM) $(OBJ)
	-$(RM) example
