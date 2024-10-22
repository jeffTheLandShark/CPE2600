CC=gcc
CFLAGS=-c -Wall -ggdb3
LDFLAGS=-lm
SOURCES=main.c parser.c vectstore.c vectmath.c csvparser.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=matlab-clone

all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)