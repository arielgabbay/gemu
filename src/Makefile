CC := gcc
CFLAGS := -Wall

OBJECTS := cpu.o mmu.o ops.o gpu.o main.o
DEPS_DIR := ../dependencies

# static libraries built here
ALSA_DIR := $(DEPS_DIR)/alsa-lib/src/.libs
ALSA_LIB := asound
WAYLAND_DIR := $(DEPS_DIR)/wayland/.libs
WAYLAND_LIB := wayland-client

define STATLIB
FULL_$(1) := $$($(1)_DIR)/lib$$($(1)_LIB).a
endef
$(foreach L,ALSA WAYLAND,$(eval $(call STATLIB,$(L))))

# acquired using sdl2-config (with some additions)
CFLAGS := -I/usr/local/include/SDL2 -D_REENTRANT
STATIC_LIBS := -L$(WAYLAND_DIR) -L$(ALSA_DIR) -L/usr/local/lib -lSDL2 -lm -ldl -lrt -l$(ALSA_LIB) -l$(WAYLAND_LIB) -lpthread
DYNAMIC_LIBS := -lSDL2

all: gemu gemu-static

$(FULL_ALSA):
	cd $(ALSA_DIR) && autoreconf -i
	cd $(ALSA_DIR) && ./configure --enable-static --disable-shared
	make -C $(ALSA_DIR)

$(FULL_WAYLAND):
	cd $(WAYLAND_DIR) && ./autogen.sh --enable-static --disable-documentation
	make -C $(WAYLAND_DIR)

gemu-static: $(OBJECTS:.o=.c) $(FULL_ALSA) $(FULL_WAYLAND)
	$(CC) $(CFLAGS) -static $^ -o $@ $(STATIC_LIBS)

gemu: $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) $^ -o $@ $(DYNAMIC_LIBS)

clean:
	rm -f $(OBJECTS)
	rm -f gemu gemu-static

.PHONY: clean

