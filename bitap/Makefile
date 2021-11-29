CC=gcc
CFLAGS=-std=c99 -Wall -Wno-stringop-truncation -O2 -g -D_POSIX_C_SOURCE=199309L

#SOURCES=horspool.c timer.c
SOURCES=bitap.c timer.c
TARGETS=$(SOURCES:.c=)
OBJECTS=$(SOURCES:.c=.o)
DEPS=$(SOURCES:.c=.d)

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

-include ($DEPS)

clean:
	rm -rf $(TARGETS) $(OBJECTS) *.o

