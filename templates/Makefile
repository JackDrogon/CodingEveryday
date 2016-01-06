# TODO: Add depency
# TODO: Add platform detection

CC 	:= g
CFLAGS 	:= -Weverything
CXX	:= g++
CXXFLAGS := -Weverything -std=c++1y
LD 	:= g++
LDFLAGS :=

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	CXXFLAGS += -g
endif


TARGET	:=
OBJS	:=


all: $(TARGET)
.PHONY: all clean

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# $(OBJS): %.o : %.cc
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	-$(RM) -rf $(OBJS) $(TARGET)
