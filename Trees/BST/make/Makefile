CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=../include/Header.h
SOURCES= ../src/Binary_search_tree.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=BINARY_SEARCH_TREE

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
