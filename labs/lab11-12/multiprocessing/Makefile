CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-ljpeg -lm
SOURCES= mandelmovie.c mandel.c jpegrw.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mandelmovie

BENCHMARK_SOURCES= benchmark.c mandel.c jpegrw.c
BENCHMARK_OBJECTS=$(BENCHMARK_SOURCES:.c=.o)
BENCHMARK_EXECUTABLE=benchmark

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

benchmark: $(BENCHMARK_OBJECTS)
	$(CC) $(BENCHMARK_OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d $(BENCHMARK_OBJECTS) $(BENCHMARK_EXECUTABLE)



