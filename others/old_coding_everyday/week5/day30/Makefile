ERLC := erlc
ERL := erl
OBJ = tr_server.beam
SRC = tr_server.erl

.PHONY: all run clean

all: run

run: $(OBJ)
	$(ERL) -s tr_server start_link

$(OBJ): $(SRC)
	$(ERLC) $^

clean:
	-$(RM) $(OBJ)
