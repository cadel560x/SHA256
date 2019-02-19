#include <stdio.h>
#include <stdint.h>

void bitprint(uint32_t x) {
	int i;

	for ( i = 0; i < 32; i++ ) {
		if (x & (1 < (31 - i))) {
			printf('1');
		}
		else {
			printf('0');
		}
	}

} // end function


int main(int argc, char *argv[]) {

	uint32_t a = 1;
	uint32_t b = 2;

	printf("a:  %08x\n", a);
	printf("b:  %08x\n", b);

	printf("&:  %08x\n",(a&b));
	printf("|:  %08x\n",(a|b));
	printf("^:  %08x\n",(a^b));
	printf("~:  %08x\n",(~a));
	printf("<<: %08x\n",(a<<1));
	printf(">>: %08x\n",(a>>1));

	return 0;

} // end main
