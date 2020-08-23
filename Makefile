CC=g++

CFLAGS=-I.
LDFLAGS= 

BIN=funktionsrechner
OBJ=Funktionsrechner.o Stack.o

main: ${OBJ}
	$(CC) -o $(BIN) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean all
clean:
	rm -f $(BIN) $(OBJ)

all: main
