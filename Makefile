CC = gcc
CFLAGS = -lncurses -I./kernel/include
SOURCES = $(wildcard ./src/*.c)
#OBJECTS = $(SOURCES:.c=.o)
EXEC = ./bin/CogitatorOS

all: $(EXEC)

$(EXEC): #$(OBJECTS)
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS)

.c.o:
	$(CC) -o -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC)