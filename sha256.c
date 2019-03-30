#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
 
 
// MACROS
//
// See Section 3.2 for definitions.
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

// See Section 4.1.2 for definition.
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3 ))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#define SWAP_UINT64(x) \
	( (((x) >> 56) & 0x00000000000000FF) | (((x) >> 40) & 0x000000000000FF00) | \
	  (((x) >> 24) & 0x0000000000FF0000) | (((x) >>  8) & 0x00000000FF000000) | \
	  (((x) <<  8) & 0x000000FF00000000) | (((x) << 24) & 0x0000FF0000000000) | \
	  (((x) << 40) & 0x00FF000000000000) | (((x) << 56) & 0xFF00000000000000) )

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
    

//K = constant value to be used for the iteration t of the hash computation.
static const uint32_t  K[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};


// Data structures
union msgblock {
	uint8_t e[64];
	uint32_t th[16];
	uint64_t s[8];
};

enum status {READ, PAD0, PAD1, FINISH};


// Function prototypes
//void sha256(FILE *input_file);
uint64_t* sha256(FILE *input_file);
int nextmsgblock(FILE *input_file, union msgblock *M, enum status *S, uint64_t *nobits);




// Entry point 
int main (int argc, char *argv[]){

	FILE *file;
	uint64_t *hash;
    
	// Check for input files
	if (argc == 1) {
		fprintf(stderr, "Error: No input files\n");	
		fprintf(stderr, "usage: %s [FILE]...\n", argv[0]);
		exit(1);
	}

	// Iterates over input files
	for (int j = 1; j < argc; j++ ) {
		file = fopen(argv[j], "r");
		
		// File check
		if ( file == NULL ) {
			fprintf(stderr, "Error: %s\n", strerror(errno));	
			exit(2);
		}

		// Run the secure hash algorithm on the current file
    		hash = sha256(file);

		// Close the current file
		fclose(file);

		// Output the resulting hash
		for(int k = 0; k < 8; k++) {
			printf("%08x", *(hash + k));
		}
		printf("\n");

	} // end loop

    return 0;
           
} // end main


// Functions implementation
//
// void sha256(FILE *input_file) {
uint64_t*  sha256(FILE *input_file) {
    uint64_t *hash = malloc(sizeof(uint64_t) * 8 ); 
    union msgblock M;
    enum status S = READ;
    uint64_t nobits = 0;
             
    uint32_t W[64];
    uint32_t a,b,c,d,e,f,g,h;
    uint32_t T1, T2;
    uint32_t H[8] = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
     };

 // For looping.
    int t;
                                                                  
//  Loop through message blocks as per page 22
//    for ( i = 0; i < 1; i++ ) {
    while (nextmsgblock(input_file, &M, &S, &nobits)) {

	// From page 22, W[t] = M[t] for 0 <= t <= 15.
	    for(t = 0; t < 16; t++) {
	       if (IS_BIG_ENDIAN) {
	       	  W[t] = M.th[t];
	       }
	       else {
    	          W[t] = SWAP_UINT32(M.th[t]);
	       } // end if-else

	    } // end loop
	                                                                           
	    for(t = 16; t < 64; ++t) {
	       W[t] = SIG1(W[t-2]) + W[t-7] + SIG0(W[t-15]) + W[t-16];
	    }
	     
       /*   // Debug
            for (t = 0; t < 64; t++) {
               printf("%08x ", W[t]);
            }
            printf("\n\n");
       */

	// Initialize a,b,c, ... ,h as per step 2, Page 22.
	    a = H[0]; b = H[1]; c = H[2]; d = H[3];
	    e = H[4]; f = H[5]; g = H[6]; h = H[7];

	// Step 3.
	    for(t = 0; t < 64; t++) {

	       T1 = h + EP1(e) + CH(e,f,g) + K[t] + W[t];
	       T2 = EP0(a) + MAJ(a,b,c);
	       h = g;
	       g = f;
	       f = e;
	       e = d + T1;
	       d = c;
	       c = b;
	       b = a;
	       a = T1 + T2;
	       
	    } // end loop

	  /*  // Debug
	    printf("%08x\n", a);
	    printf("%08x\n", b);
	    printf("%08x\n", c);
	    printf("%08x\n", d);
	    printf("%08x\n", e);
	    printf("%08x\n", f);
	    printf("%08x\n", g);
	    printf("%08x\n", h);
            printf("\n\n");
          */
	
	// Step 4.
	    H[0] = a + H[0];
	    H[1] = b + H[1];
	    H[2] = c + H[2];
	    H[3] = d + H[3];
	    H[4] = e + H[4];
	    H[5] = f + H[5];
	    H[6] = g + H[6];
	    H[7] = h + H[7];

    } // end loop

    // Debug
    // printf("%08x%08x%08x%08x%08x%08x%08x%08x\n",  H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);

	    for(t = 0; t < 8; t++) {
	*(hash + t) = H[t];
    }

   return hash;

} // end function


int nextmsgblock(FILE *input_file, union msgblock *M, enum status *S, uint64_t *nobits) {

	uint64_t nobytes;

	// If we have finished all the message blocks, then S should be FINISH
	if (*S == FINISH) {
		return 0;
	}
	
	// Check if we need another block full of padding 
	if (*S == PAD0 || *S == PAD1) {
		// Set the first 56 bytes to all zero bits
		for (int i = 0; i < 56; i++) {
			M->e[i] = 0x00;
		}

		// Set the last 64 bits to the number of bits in the file (big-endian)
		if (IS_BIG_ENDIAN) {
			M->s[7] = *nobits;
		}
		else {
			M->s[7] = SWAP_UINT64(*nobits);
		}

		// Tell S we are finished
		*S = FINISH;

		if (*S == PAD1) {
			M->e[0] = 0x80;
		}

		// Keep the loop in sha256 going for one more iteration
		return 1;

	} // end if


	// If we get down here, we haven't finished reading the file
	// Starts reading current input file pointed by 'f' pointer
	*S = READ;

	nobytes = fread(M->e, 1, 64, input_file);
	
	//printf("Read %2llu bytes\n", nobytes);
	
	// Keep track of the number of bytes we've read
	*nobits = *nobits + (nobytes * 8);

	// If we read less than 56 bytes, we can put all padding in this message block
	if (nobytes < 56 ) {
		// printf("I've found a block with less than 55 bytes!\n");
		 
		// And the one bit, per standard
		M->e[nobytes] = 0x80;

		// Add zero bits unit the last 64 bits
		while (nobytes < 56) {
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;

		} // end loop

		// Append the file size in bits as an unsigned 64 bit int (big-endian)
		if (IS_BIG_ENDIAN) {
			M->s[7] = *nobits;
		}
		else {
			M->s[7] = SWAP_UINT64(*nobits);
		}

		// Tell S we have finished
		*S = FINISH;
	
	// Otherwise, check if we can put some padding int this message block	
	}
	else if (nobytes < 64) {
		// Tell S we need another mesage block, with padding but no one bit
		*S = PAD0;

		// Put the one bit into the current block
		M->e[nobytes] = 0x80;

		// Pad the rest of the block with zero bits
		while (nobytes < 64) {
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;

	        } // end loop

	}
	// Otherwise, check if we're just at the end of the file
	else if (feof(input_file)) {
		// Tell S that we need another message block with all the padding
		*S = PAD1;

	} // end if-else if


	/* // DEBUG
	for (int i = 0; i < 64; i++) {
		printf("%x ", M.e[i]);
	}
	printf("\n\n");
	*/

        //Return 1 to get this function to be called again
	return 1;

} // end function

