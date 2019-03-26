#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

union msgblock {
	uint8_t e[64];
	uint32_t t[16];
	uint64_t s[8];
};

enum status {READ, PAD0, PAD1, FINISH};

int main(int argc, char *argv[]) {
	union msgblock M;

	uint64_t nobits = 0;
	uint64_t nobytes;

	enum status S = READ;

	FILE *f;

	// Check for input files
	if (argc == 1) {
		fprintf(stderr, "Error: No input files\n");	
		fprintf(stderr, "usage: %s [FILE]...\n", argv[0]);
		exit(1);
	}

	// Iterates over input files
	for (int j = 1; j < argc; j++ ) {
		f = fopen(argv[j], "r");
		
		// File check
		if ( f == NULL ) {
			fprintf(stderr, "Error: %s\n", strerror(errno));	
			exit(2);
		}
	
		// Starts reading current input file pointed by 'f' pointer
		S = READ;
		while (S == READ) {
			nobytes = fread(M.e, 1, 64, f);
			printf("Read %2llu bytes\n", nobytes);
			nobits = nobits + (nobytes * 8);
			if (nobytes < 56 ) {
				printf("I've found a block with less than 55 bytes!\n");
				M.e[nobytes] = 0x80;
				while (nobytes < 56) {
					nobytes = nobytes + 1;
					M.e[nobytes] = 0x00;
	
				} // end loop
	
				M.s[7] = nobits;
				S = FINISH;
			}
			else if (nobytes < 64) {
				S = PAD0;
				M.e[nobytes] = 0x80;
				while (nobytes < 64) {
					nobytes = nobytes + 1;
					M.e[nobytes] = 0x00;
	
				} // end loop
			}
			else if (feof(f)) {
				S = PAD1;
	
			} // end if-else if
	
		} // end loop
	
		fclose(f);
	
		if (S == PAD0 || S == PAD1) {
			for (int i = 0; i < 56; i++) {
				M.e[i] = 0x00;
			}
	
			M.s[7] = nobits;
	
		} // end if
	
		if (S == PAD1) {
			M.e[0] = 0x80;
		}
	
		for (int i = 0; i < 64; i++) {
			printf("%x ", M.e[i]);
		}
	
		printf("\n\n");

	} // end loop


	return 0;

} // end main
