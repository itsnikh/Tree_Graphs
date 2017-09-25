CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=../include/Header.h
SOURCES= ../src/Red_Black_tree.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=RED_BLACK_TREE

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
