CC = gcc
CFLAGS = -lncurses -I./kernel/include
SOURCES = ./src/main.c ./src/ps1.c
#OBJECTS = $(SOURCES:.c=.o)
EXEC = bin/CogitatorOS

all: $(EXEC)

$(EXEC): #$(OBJECTS)
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS)

.c.o:
	$(CC) -o $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) $(EXEC)