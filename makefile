CC = g++
CFLAGS = -Wall -g
PROGRAM = aes
LIBS = libAes

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).o $(LIBS).o
	$(CC) $(CFLAGS) $(LIBS).o $(PROGRAM).o -o $(PROGRAM)

$(LIBS).o: $(LIBS).hpp $(LIBS).cpp
	$(CC) $(CFLAGS) -c $(LIBS).cpp

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f *.o $(PROGRAM)
