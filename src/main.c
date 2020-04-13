#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

#include <SDL.h>

#include "cpu.h"
#include "gpu.h"

struct args {
	uint8_t boot_rom_fname[PATH_MAX];
	uint8_t rom_fname[PATH_MAX];
	int debugging;
};

#define PRINT_USAGE_AND_FAIL(prog_name) \
	do { \
		printf("Usage: %s <rom_name> [-b <boot_rom>]\n", prog_name); \
		retval = 1; \
		goto cleanup; \
	} while (0)

int parse_args(int argc, char * const argv[], struct args * dst) {
	int c, retval;
	memset(dst, 0, sizeof(*dst));
	strcpy(dst->boot_rom_fname, "../boot/dmg_boot.bin");
	retval = 0;
	c = getopt(argc, argv, "b:d");
	while (c != -1) {
		switch (c) {
			case 'b':
				strncpy(dst->boot_rom_fname, optarg, strlen(optarg));
				break;
			case 'd':
				dst->debugging = 1;
				break;
			case '?':
				PRINT_USAGE_AND_FAIL(argv[0]);
				break;
		}
		c = getopt(argc, argv, "b:");
	}
	if (optind == argc - 1) {
		strcpy(dst->rom_fname, argv[optind]);
	}
	else {
		PRINT_USAGE_AND_FAIL(argv[0]);
	}
cleanup:
	return retval;
}

int main(int argc, char * const argv[]) {
	struct args args = {0};
	struct gpu_state * gpu_state = NULL;
	int boot_fd = -1, rom_fd = -1;
	mmu_ret_t mmu_init_ret;
	int ret = 1;
	// Parse program arguments
	if (parse_args(argc, argv, &args) != 0) {
		goto cleanup;
	}
	// Open files given
	boot_fd = open(args.boot_rom_fname, O_RDONLY);
	if (boot_fd < 0) {
		fprintf(stderr, "Failed to open BIOS file.\n");
		goto cleanup;
	}
	rom_fd = open(args.rom_fname, O_RDONLY);
	if (rom_fd < 0) {
		fprintf(stderr, "Failed to open ROM file.\n");
		goto cleanup;
	}
	// Init MMU
	mmu_init_ret = init_mmu(boot_fd, rom_fd);
	close(boot_fd);
	close(rom_fd);
	if (mmu_init_ret != MMU_SUCCESS) {
		fprintf(stderr, "Failed to initialize MMU.\n");
		goto cleanup;
	}
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "CreateWindow failed: %s\n", SDL_GetError());
		goto cleanup;
	}
	// Init GPU
	gpu_state = init_gpu();
	if (gpu_state == NULL) {
		goto cleanup;
	}
	// Start CPU
	ret = cpu_main(gpu_state, args.debugging);
	ret = 0;
cleanup:
	exit_gpu(gpu_state);
	SDL_Quit();
	if (boot_fd >= 0) {
		close(boot_fd);
	}
	if (rom_fd >= 0) {
		close(rom_fd);
	}
	return ret;
}

