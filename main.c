#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "cpu.h"

struct args {
	uint8_t boot_rom_fname[PATH_MAX];
	uint8_t rom_fname[PATH_MAX];
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
	retval = 0;
	c = getopt(argc, argv, "b:");
	while (c != -1) {
		switch (c) {
			case 'b':
				strncpy(dst->boot_rom_fname, optarg, strlen(optarg));
				break;
			case '?':
				PRINT_USAGE_AND_FAIL(argv[0]);
				break;
		}
		c = getopt(argc, argv, "b:");
	}
	if (optind == argc - 1) {
		strncpy(dst->rom_fname, argv[optind], strlen(argv[optind]));
	}
	else {
		PRINT_USAGE_AND_FAIL(argv[0]);
	}
cleanup:
	return retval;
}

int main(int argc, char * const argv[]) {
	struct args args = {0};
	if (parse_args(argc, argv, &args) != 0) {
		return 1;
	}
	return 0;
}

