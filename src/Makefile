CC := gcc
CFLAGS := -Wall

OBJECTS := cpu.o mmu.o ops.o gpu.o main.o
CFLAGS := -I../others/sdl/include # -L../others/sdl/build/.libs 

all: gemu

gemu: $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) $^ -o $@ -lSDL2

clean:
	rm -f $(OBJECTS)
	rm -f gemu

.PHONY: clean

