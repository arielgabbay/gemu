#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <pthread.h>

#include "cpu.h"
#include "gpu.h"
#include "input.h"

struct args {
	char boot_rom_fname[PATH_MAX];
	char rom_fname[PATH_MAX];
	char sav_fname[PATH_MAX];
	int debug;
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
	c = getopt(argc, argv, "b:ds:");
	while (c != -1) {
		switch (c) {
			case 'b':
				strncpy(dst->boot_rom_fname, optarg, sizeof(dst->boot_rom_fname));
				break;
			case 's':
				strncpy(dst->sav_fname, optarg, sizeof(dst->sav_fname));
				break;
			case 'd':
				dst->debug = 1;
				break;
			case '?':
				PRINT_USAGE_AND_FAIL(argv[0]);
				break;
		}
		c = getopt(argc, argv, "b:");
	}
	if (optind == argc - 1) {
		strncpy(dst->rom_fname, argv[optind], sizeof(dst->rom_fname));
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
	int boot_fd = -1, rom_fd = -1, sav_fd = -1;
	mmu_ret_t mmu_init_ret;
	int ret = 1;
	pthread_t input_thread;
	int init_mutex = 0;
	char * game_title = NULL;
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
	if (strlen(args.sav_fname) > 0) {
		sav_fd = open(args.sav_fname, O_RDWR | O_CREAT);
		if (sav_fd < 0) {
			fprintf(stderr, "Failed to open SAV file.\n");
			goto cleanup;
		}
	}
	// Init MMU
	mmu_init_ret = init_mmu(boot_fd, rom_fd, sav_fd, &game_title);
	close(boot_fd);
	boot_fd = -1;
	if (mmu_init_ret != MMU_SUCCESS) {
		fprintf(stderr, "Failed to initialize MMU.\n");
		goto cleanup;
	}
	// Init GPU
	gpu_state = init_gpu(game_title);
	if (gpu_state == NULL) {
		goto cleanup;
	}
	// Start input thread
	if (pthread_mutex_init(&input_lock, NULL)) {
		fprintf(stderr, "Failed to init input mutex\n");
		goto cleanup;
	}
	init_mutex = 1;
	if (pthread_create(&input_thread, NULL, input_main, NULL)) {
		fprintf(stderr, "Failed to start input thread\n");
		goto cleanup;
	}
	// Start CPU
	ret = cpu_main(gpu_state, args.debug);
	// Stop input thread
	input_quit = 1;
	pthread_join(input_thread, NULL);
cleanup:
	if (init_mutex) {
		pthread_mutex_destroy(&input_lock);
	}
	exit_gpu(gpu_state);
	if (boot_fd >= 0) {
		close(boot_fd);
	}
	if (rom_fd >= 0) {
		close(rom_fd);
	}
	if (sav_fd >= 0) {
		close(sav_fd);
	}
	return ret;
}

