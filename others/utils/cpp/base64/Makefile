# TODO: Add depency
# TODO: Add platform detection
# TODO: Add format

CC       := g
CFLAGS   := -Weverything
CXX      := g++
CXXFLAGS := -Weverything -std=c++1y
LD       := g++
LDFLAGS  :=

ifeq ($(DEBUG),yes)
	CFLAGS   += -g
	CXXFLAGS += -g
endif


TARGET := base64_test
OBJS   := base64_test.o base64.o


all: $(TARGET)
.PHONY: all clean

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

tags:
	ctags -R --c++-kinds=+p+l+x+c+d+e+f+g+m+n+s+t+u+v --fields=+liaS --extra=+q --extra=+f

gtags:
	gtags -c

clean:
	-$(RM) -rf $(OBJS) $(TARGET)
