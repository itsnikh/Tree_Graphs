CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=../include/Header.h
SOURCES= ../src/mst_prims.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Prims_Algorithm

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
