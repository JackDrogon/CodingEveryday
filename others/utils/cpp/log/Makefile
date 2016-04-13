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

ifeq ($(DEBUG),yes)
	CFLAGS   += -g
	CXXFLAGS += -g
	LDFLAGS += -g
endif


TARGET := logger
TARGETS := test_file_logger test_logger
OBJ1 = test_file_logger.o
OBJ2 = test_logger.o
BOBJS   := logger.o sync_log_device.o async_log_device.o buffer.o


all: $(TARGET)
.PHONY: all clean run $(TARGET)

$(TARGET) : $(TARGETS)

test_file_logger: $(OBJ1) $(BOBJS)
	$(LD) $(LDFLAGS) -o $@ $^

test_logger: $(OBJ2) $(BOBJS)
	$(LD) $(LDFLAGS) -o $@ $^

run: $(TARGETS)
	./$(TARGETS)
tags:
	@ctags -R --c++-kinds=+p+l+x+c+d+e+f+g+m+n+s+t+u+v --fields=+liaS --extra=+q --extra=+f

gtags:
	@gtags -c

clean:
	-$(RM) -rf $(OBJ1) $(OBJ2) $(BOBJS) $(TARGETS)
