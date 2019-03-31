# Theory of Algorithms Project 2019
#### Lecturer: *Dr.Ian McLoughlin*
#### Student Name: *Javier Mantilla*
#### Student ID: *G00329649*

## *Introduction for SHA256*
SHA-256 stands for Secure Hash Algorithm – 256 bit and is a type of hash function commonly used in Blockchain. A hash function is a type of mathematical function which turns data into a fingerprint of that data called a hash. It’s like a formula or algorithm which takes the input data and turns it into an output of a fixed length, which represents the fingerprint of the data.</br>
The input data can literally be any data, whether it’s the entire Encyclopedia Britannica, or just the number ‘1’. A hash function will give the same hash for the same input always no matter when, where and how you run the algorithm. Equally interestingly, if even one character in the input text or data is changed, the output hash will change. Also, a hash function is a one-way function, thus it is impossible to generate back the input data from its hash. So, you can go from the input data to the hash but not from the hash to the input data.</br>

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

## *Video Links* 
* Hash standard intro: https://web.microsoftstream.com/video/6c22658e-7e5a-421a-b7f9-f0206741ca40
* Prime Cube Roots: https://web.microsoftstream.com/video/e5e7f5d8-3d2f-4115-9eaa-d9b1d6a91c4e
* SHA256 Part 1: https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366
* SHA256 Part 2: https://web.microsoftstream.com/video/2a86a2ac-aafb-46e0-a278-a3faa1d13cbf
* Unions in C: https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb
* Padding for C: https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13
* Padding for C part 2: https://web.microsoftstream.com/video/200e71ec-1dc1-47a4-9de8-6f58781e3f38
* Finishing the SHA256 Algorithms: https://web.microsoftstream.com/video/f823809a-d8df-4e12-b243-e1f8ed76b93f
