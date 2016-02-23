# TODO: Add depency
# TODO: Add platform detection
# TODO: Add format
# TODO: Delivery params to run
# TODO: Add auto generate Project Makefile with TARGET from file name
# TODO: Use wildchard && vpath to generate OBJS
# TODO: Refer to erlang.mk && kbuild

CC       := g
CFLAGS   := -Weverything
CXX      := g++
CXXFLAGS := -Weverything -std=c++1y
LD       := g++
LDFLAGS  :=
LLVM-CC  := llvm-gcc -S -emit-llvm

ifeq ($(DEBUG),yes)
	CFLAGS   += -g
	CXXFLAGS += -g
endif


TARGET := hello
OBJS   := hello.ll


all: $(TARGET)
.PHONY: all clean run $(TARGET)

$(TARGET): $(OBJS)

# $(OBJS): %.o : %.cc
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJS): %.ll : %.c
	$(LLVM-CC) $<

run: $(TARGET)
	./$(TARGET)

tags:
	ctags -R --c++-kinds=+p+l+x+c+d+e+f+g+m+n+s+t+u+v --fields=+liaS --extra=+q --extra=+f

gtags:
	gtags -c

clean:
	-$(RM) -rf $(OBJS) $(TARGET)
