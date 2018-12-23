#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>

#define OPTIONS "hd"

void usage(char* progname)
{
	printf("Display btime of a given file in UNIX time format.\n");
	printf("Usage: %s [options] FILE\n", progname);
	printf(" -h        Show this help\n");
	printf(" -d        Passess the file to statx via file descriptor\n");
}

int main(int argc, char**argv)
{
	struct statx stx = { 0, };
	bool via_fd = false;
	int rc = 0;
	int c;

	while ((c = getopt(argc, argv, OPTIONS)) != -1) {
		switch (c) {
		case 'h':
			usage(argv[0]);
			return EXIT_SUCCESS;
		case 'd':
			via_fd = true;
			break;
		case '?':
			usage(argv[0]);
			return EXIT_FAILURE;
		}
	}

	if (argc != (optind + 1)) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	if (via_fd) {
		int fd = open(argv[optind], O_PATH|O_NOFOLLOW);
		rc = statx(fd, "", AT_EMPTY_PATH, STATX_BTIME, &stx);
		close(fd);
	} else {
		rc = statx(AT_FDCWD, argv[optind], AT_SYMLINK_NOFOLLOW, STATX_BTIME, &stx);
	}
	if (rc == 0) {
		if (stx.stx_btime.tv_sec != 0) {
			printf("%u.%u\n", stx.stx_btime.tv_sec, stx.stx_btime.tv_nsec);
		} else {
			printf("-\n");
		}
	} else {
		perror("statx");
	}

	return rc;
}
