# TODO: Add depency
# TODO: Add platform detection
# TODO: Add format
# TODO: Delivery params to run
# TODO: Add auto generate Project Makefile with TARGET from file name
# TODO: Use wildchard && vpath to generate OBJS
# TODO: Refer to erlang.mk && kbuild
# TODO: Remove -Weverything in Linux
# TODO: build-in memcpy

CC       := g
CFLAGS   := -Weverything
CXX      := g++
CXXFLAGS := -Weverything -std=c++1y
LD       := g++
LDFLAGS  :=

ifeq ($(DEBUG),yes)
	CFLAGS   += -g -pg -ggdb3
	CXXFLAGS += -g -pg -ggdb3
else
	CFLAGS   += -DNDEBUG
	CXXFLAGS += -DNDEBUG
endif


SERVER := socket_server_test01
SERVER_OBJ := socket_server_test01.o
CLIENT := socket_client_test01
CLIENT_OBJ := socket_client_test01.o
TARGET := $(SERVER) $(CLIENT)
OBJS   := inet_address.o socket.o


all: $(TARGET)
.PHONY: all clean run $(TARGET)

$(SERVER): $(SERVER_OBJ) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_OBJ) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# $(OBJS): %.o : %.cc
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

tags:
	ctags -R --c++-kinds=+p+l+x+c+d+e+f+g+m+n+s+t+u+v --fields=+liaS --extra=+q --extra=+f

gtags:
	gtags -c

clean:
	-$(RM) -rf $(OBJS) $(TARGET) $(SERVER_OBJ) $(CLIENT_OBJ)
