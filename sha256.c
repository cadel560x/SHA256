#include <stdio.h>
#include <stdint.h>
 
void sha256();
 
// See Section 3.2 for definitions.
// uint32_t rotr(uint32_t n, uint32_t x);
// uint32_t shr(uint32_t n, uint32_t x);
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

// See Section 4.1.2 for definition.
// uint32_t sig0(uint32_t x);
// uint32_t sig1(uint32_t x);
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3 ))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

 

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))


    
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

int main (int argc, char *argv[]){
    
    sha256();
        
    return 0;
           
} // end main
            

void sha256() {
             
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

// the current message block
    uint32_t M[16] = {0 , 0 , 0 ,0 ,0 ,0 , 0, 0
//                      ,0 , 0 , 0 ,0 ,0 ,0 , 0, 0
     };
                                                             
 // For looping.
    int i, t;  
                                                                  
//  Loop through message blocks as per page 22
    for ( i = 0; i < 1; i++ ) {

// From page 22, W[t] = M[t] for 0 <= t <= 15.
    for(t = 0; t < 16; t++) {
       W[t] = M[t];
    }
                                                                           
    for(t = 16; t < 64; ++t) {
       W[t] = SIG1(W[t-2]) + W[t-7] + SIG0(W[t-15]) + W[t-16];
    }
                                                                                  
                                                                                   
// Initialize a,b,c, ... ,h as per step 2, Page 22.
    a = H[0]; b = H[1]; c = H[2]; d = H[3];
    d = H[4]; e = H[5]; f = H[6]; f = H[7];
                                                                                          
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

    printf("%x %x %x %x %x %x %x %x : ",  H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);

} // end function

//uint32_t sig0(uint32_t x) {
// See Sections 3.2 and 4.1.2 for definitions.
//    return (rotr(7,x) ^ rotr(18, x) ^ shr(3,x));
//}
                                                                                                                                                                     
//uint32_t sig1(uint32_t x) {
// See Sections 3.2 and 4.1.2 for definitions.
//    return (rotr(17,x) ^ rotr(19,x) ^ shr(10,x));
//}

//uint32_t rotr(uint32_t n, uint32_t x) {
// See Section 3.2 for definition.
//    return (x >> n) | (x << (32-n));
//}

//uint32_t shr(uint32_t n, uint32_t x) {
//    return (x >> n);
//}