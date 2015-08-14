CC = gcc
CXX = g++
CFLAGS = -Weverything -g -O2
CXXFLAGS = -Weverything -g -O2
LD = gcc

# TODO Add colorful display && echo
# TODO Add debug mode && only debug mode use -g -O0
# TODO Add targets compile function

TARGETS = bin timer_test progress_timer_test

.PHONY : all clean test

all : $(TARGETS)

bin :
	- mkdir -p bin

timer_test : bin timer_test.cc
	$(CXX) $(CXXFLAGS) -o bin/$@ timer_test.cc

progress_timer_test : bin progress_timer_test.cc
	$(CXX) $(CXXFLAGS) -o bin/$@  progress_timer_test.cc


clean :
	-$(RM) -rf bin
	-$(RM) -rf timer_test timer_test.dSYM

test:
