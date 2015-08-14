RUSTC = rustc
RUSTFLAGS =
RUSTFLAGS_LTO = -O -C lto
STRIP = strip
TARGET = hello

.PHONY : all clean

all : $(TARGET)

% : %.rs
	$(RUSTC) $(RUSTFLAGS) $<
	$(STRIP) $@

clean :
	-$(RM) -rf $(TARGET)
