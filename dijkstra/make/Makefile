CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=../include/Header.h
SOURCES= ../src/sssp_dijkstra.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Dijkstra_Algorithm

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
