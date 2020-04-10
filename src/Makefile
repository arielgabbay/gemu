CC := gcc
CFLAGS := -Wall

OBJECTS := cpu.o mmu.o ops.o main.o 

all: gemu

gemu: $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJECTS)
	rm -f gemu

.PHONY: clean

