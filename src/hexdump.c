#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int ch;
	long offset = 0;

	while ((ch = getopt(argc, argv, "")) != -1) {
		switch (ch) {
		default:
			fprintf(stderr, "usage: %s [file ...]\n", argv[0]);
			return EXIT_FAILURE;
		}
	}

	if (argc == optind) {
		argc++;
		argv[optind] = "-";
	}

	for (; optind < argc; optind++) {
		FILE *f;
		unsigned char data[16];
		size_t nread;
		size_t i;

		memset(data, 0, 16);

		if (strcmp("-", argv[optind]) == 0) {
			f = stdin;
		} else if ((f = fopen(argv[optind], "rb")) == NULL) {
			warn("%s", argv[optind]);

			continue;
		}

		do {
			printf("%08lx ", offset);

			nread = fread(data, sizeof(unsigned char), 16, f);

			for (i = 0; i < nread; ++i) {
				if (i == 8) {
					printf("  ");
				} else {
					printf(" ");
				}

				printf("%02x", data[i]);
			}

			for (i = nread; i < 16; ++i) {
				if (i == 8) {
					printf("  ");
				} else {
					printf(" ");
				}

				printf("  ");
			}

			printf("  |");

			for (i = 0; i < nread; ++i) {
				if (isprint(data[i])) {
					putchar(data[i]);
				} else {
					putchar('.');
				}
			}

			printf("|\n");

			offset += (long)nread;
		} while (feof(f) == 0 && ferror(f) == 0);

		fclose(f);
	}

	printf("%08lx\n", offset);

	return 0;
}
