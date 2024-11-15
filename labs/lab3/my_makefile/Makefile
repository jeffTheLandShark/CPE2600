CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-l ncurses
SOURCES=snake.c arguments_parser.c field.c game.c score_file.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=snake_game.exe

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
