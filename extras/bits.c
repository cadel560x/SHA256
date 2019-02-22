#include <stdio.h>
#include <stdint.h>

void bitprint(uint32_t x) {
	int i;
	uint32_t one = 1;

	for ( i = 0; i < 32; i++ ) {
		if (( one << (31 - i)) & x) {
			printf("1");
		}
		else {
			printf("0");
		}
	}

} // end function


uint32_t rotl(uint32_t x, int n) {
	return ((x<<n) | (x >> (32 - n)));
} // end function


uint32_t rotr(uint32_t x, int n) {
	return  ((x<< (32-n )) | (x>> n));
} // end function



int main(int argc, char *argv[]) {

	// uint32_t a = 1;
	// uint32_t b = 2;

	uint32_t a = 0x428a2f98;
	uint32_t b = 0x71374491;

	printf("hex a:  %08x\n", a);
	printf("hex b:  %08x\n", b);

	printf("   a: "); bitprint(a); printf("\n");
	printf("   b: "); bitprint(b); printf("\n");

	// printf("&:  %08x\n",(a&b));
	printf(" a&b: "); bitprint(a&b); printf("\n");
	// printf("|:  %08x\n",(a|b));
	printf(" a|b: "); bitprint(a|b); printf("\n");
	// printf("^:  %08x\n",(a^b));
	printf(" a^b: "); bitprint(a^b); printf("\n");
	// printf("~:  %08x\n",(~a));
	printf("  ~a: "); bitprint(~a); printf("\n");
	// printf("<<: %08x\n",(a<<1));
	printf("a<<1: "); bitprint(a<<1); printf("\n");
	// printf(">>: %08x\n",(a>>1));
	printf("a>>1: "); bitprint(a>>1); printf("\n");

	printf("a<<3: "); bitprint(a<<3); printf("\n");
	printf("a>>3: "); bitprint(a>>3); printf("\n");

	printf("\n");
	printf("     a<<3: "); bitprint(a<<3); printf("\n");
	printf("    a>>29: "); bitprint(a>>29); printf("\n");
	printf("rotl(a,3): "); bitprint(rotl(a,3)); printf("\n");

	printf("\n");
	printf("rotr(a,3): "); bitprint(rotr(a,3)); printf("\n");

	return 0;

} // end main
