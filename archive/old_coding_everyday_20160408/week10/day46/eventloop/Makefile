# TODO: Add depency

CC 	:= clang
CFLAGS 	:= -Weverything
CXX	:= clang++
CXXFLAGS := -Weverything -std=c++1y
LD 	:= clang++
LDFLAGS :=

TARGET	:= event_loop_test
OBJS	:= event_loop_test.o channel.o event_loop.o poller.o

all: $(TARGET)
.PHONY: all clean

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# $(OBJS): %.o : %.cc
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	-$(RM) -rf $(OBJS) $(TARGET)
