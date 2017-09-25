CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=../include/Header.h
SOURCES= ../src/AVL_Binary_tree.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=AVL_BINARY_TREE

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
