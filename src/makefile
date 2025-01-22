
CC = gcc
CFLAGS = -I../include -lncurses
SOURCES = main.c ps1.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = CogitatorOS

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(CFLAGS)

.c.o:
	$(CC) -o $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) $(EXEC)