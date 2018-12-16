#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char**argv)
{
	struct statx stx = { 0, };
	int rc = 0;

	if (argc <= 1 || argc > 2) {
		printf("Prints btime of a given file in UNIX time format.\n");
		printf("Usage: %s FILE\n", argv[0]);
		return EXIT_SUCCESS;
	}

	rc = statx(AT_FDCWD, argv[1], 0, STATX_BTIME, &stx);
	if (rc == 0) {
		printf("%u.%u\n", stx.stx_btime.tv_sec, stx.stx_btime.tv_nsec);
	} else {
		perror("statx");
	}
	return rc;
}