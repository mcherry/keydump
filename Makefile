CC=gcc
CFLAGS=-framework ApplicationServices -framework Carbon
STRIP=strip
SOURCES=keydump.c
EXECUTABLE=keydump

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)
	$(STRIP) $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
