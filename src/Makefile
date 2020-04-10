CC := gcc
CFLAGS := -Wall

OBJECTS := cpu.o mmu.o ops.o gpu.o main.o
# acquired using sdl2-config
CFLAGS := -I/usr/local/include/SDL2 -D_REENTRANT
STATIC_LIBS := -L../others/alsa-lib-1.1.3/src/.libs -L/usr/local/lib -lSDL2 -lm -ldl -lrt -lasound -lpthread
DYNAMIC_LIBS := -lSDL2

all: gemu gemu-static

gemu-static: $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) -static $^ -o $@ $(STATIC_LIBS)

gemu: $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) $^ -o $@ $(DYNAMIC_LIBS)

clean:
	rm -f $(OBJECTS)
	rm -f gemu gemu-static

.PHONY: clean

