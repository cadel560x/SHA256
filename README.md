# Theory of Algorithms Project 2019
#### Lecturer: *Dr. Ian McLoughlin*
#### Student Name: *Javier Mantilla*
#### Student ID: *G00329649*

***

## *Introduction for SHA256*
SHA-256 stands for Secure Hash Algorithm – 256 bit and is a type of hash function commonly used in Blockchain. A hash function is a type of mathematical function which turns data into a fingerprint of that data called a hash. It’s like a formula or algorithm which takes the input data and turns it into an output of a fixed length, which represents the fingerprint of the data.</br>
The input data can literally be any data, whether it’s the entire Encyclopedia Britannica, or just the number ‘1’. A hash function will give the same hash for the same input always no matter when, where and how you run the algorithm. Equally interestingly, if even one character in the input text or data is changed, the output hash will change. Also, a hash function is a one-way function, thus it is impossible to generate back the input data from its hash. So, you can go from the input data to the hash but not from the hash to the input data.</br>

***

## [Steps](https://en.wikipedia.org/wiki/SHA-2)
1. Initialize hash values: </br>
The first step is to initialize the first 32 bits of the fractional part - **H[8]** - into 8 variables or primes of 4 bits each.

2. Initialize array of round constants: </br>
The 2nd step is to initialize the 64 binary words - **K[64]** - into characterised by the first 32 bits of the fractional parts of the cube roots of the first 64 prime numbers. In other words, the cube roots of the first 64 prime numbers is found as well as the fractional parts of those values. From those fractional parts, the first 32 bits are used for the 64 binary words.

3. Pre-processing (Padding): </br>
The original message starts with a length of **L** bits. A single 1 bit is added at the end followed by a **K** number of *'0'* bits in which K is the *smallest positive integer* such that **L + 1 + K = 448 mod 512**. Finally, add **L** at the end of the message, the original bits with which we started, represented by exactly 64 bits.

4. Process the message in successive 512-bit chunks: </br>
&nbsp;&nbsp;&nbsp;&nbsp;Break the message into 512-bit blocks and for each blocks create a create 64 words - **W[64]** - of 32 bits each as follows:
      1. *first 16* - split M in 32 bit blocks
      2. *remaining 48* - obtained with the formula found on the **Archived NIST Technical Series Publication** in **[Section 6.2.2, Part 1](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

5. Working variables: </br>
Initialize the working variables to the current hash value as per **[Section 6.2.2, Part 2](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

6. Compression function: </br>
Do 64 rounds consisting of the initializations in **[Section 6.2.2, Part 3](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

7. Current hash value: </br>
Add the compressed chunk to the current hash value as per **[Section 6.2.2, Part 4](https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977)**

9. Produce the final hash value (big-endian): </br>
Implement the cryptographic hash function just described by converting the little endians to big endians to allow bigger values to be outputted.

***

## Run
First and foremost, you will need to install [the GCC Compiler](http://www.codebind.com/cprogramming/install-mingw-windows-10-gcc/) (you might need to restart your computer after the installation is completed and [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) (if not already installed).

1. **Clone Repo**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Open your terminal/cmd in the folder you wish to download the repository and execute the following </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$ git clone https://github.com/cadel560x/SHA256.git```

2. **Command Prompt**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Navigate into the folder you decided to download the repository using the terminal/cmd </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$ cd SHA256```

3. **Compile**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Now compile the code using the following command </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$ gcc -o sha256 sha256.c``` 

4. **Run**

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Now, run the code:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For help and usage:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -h```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For hashing a file:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -f abc.txt```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For hashing multiple files:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -f empty.txt abc.txt string_448bits.txt string_896bits.txt```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For hashing a string:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -s abc```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For hashing multiple strings:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -s "" abc abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnop
qrsmnopqrstnopqrstu```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To activate debug flag:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -d -f abc.txt```</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To activate SHA224:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;```$./sha256 -t sha224 -f abc.txt```

***

## *Validation*
The hashes produced by this program can be validated against the following test vectors:  
[Test vectors for SHA-1, SHA-2 and SHA-3](https://www.di-mgt.com.au/sha_testvectors.html)  

Or using the OpenSSL utility  
```$openssl sha256 file```

***

## *References*
* C: https://en.wikipedia.org/wiki/C_(programming_language) <br/>
* Sha256: https://en.wikipedia.org/wiki/SHA-2 <br/>
* fread():http://www.runoob.com/cprogramming/c-function-fread.html</br>
* memcpy(): https://blog.csdn.net/tigerjibo/article/details/6841531</br>
* swap_uint32() and swap_uint64(): https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func</br>
* Secure Hash Algorithm Doc: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
* Secure Hash Standard Link for references sections: https://www.nist.gov/publications/secure-hash-standard
* Test vectors for SHA-1, SHA-2 and SHA-3: https://www.di-mgt.com.au/sha_testvectors.html  
* SHA256 Online Converter: http://www.unit-conversion.info/texttools/sha/
* C Language Operators: https://www.studytonight.com/c/operators-in-c.php
* Unions and Structures in C: https://www.quora.com/Does-structures-and-unions-have-addresses-like-variables-and-functions-in-C
* Tilde bitwise operator: https://stackoverflow.com/questions/3952122/what-does-operator-do
* Macro for 64 bit little to big endian conversion:
https://blogs.oracle.com/solaris/optimizing-byte-swapping-for-fun-and-profit-v2

***

## *Video Links* 
* Hash standard intro: https://web.microsoftstream.com/video/6c22658e-7e5a-421a-b7f9-f0206741ca40
* Prime Cube Roots: https://web.microsoftstream.com/video/e5e7f5d8-3d2f-4115-9eaa-d9b1d6a91c4e
* SHA256 Part 1: https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366
* SHA256 Part 2: https://web.microsoftstream.com/video/2a86a2ac-aafb-46e0-a278-a3faa1d13cbf
* Unions in C: https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb
* Padding for C: https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13
* Padding for C part 2: https://web.microsoftstream.com/video/200e71ec-1dc1-47a4-9de8-6f58781e3f38
* Finishing the SHA256 Algorithms: https://web.microsoftstream.com/video/f823809a-d8df-4e12-b243-e1f8ed76b93f
