CC=gcc
CFLAGS=-c
SOURCES=main.c Files.c Cache.c
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=app

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@
