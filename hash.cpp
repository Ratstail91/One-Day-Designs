#include <cstdint>
#include <iostream>

//http://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
//hash a single 32-bit integer
unsigned uinthash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

//hash a byte array into a 32-bit integer
unsigned fnv_hash_1a_32(void *key, int len) {
	unsigned char *p = static_cast<unsigned char*>(key);
	unsigned h = 0x811c9dc5;
	for (int i = 0; i < len; i++) {
		h = ( h ^ p[i] ) * 0x01000193;
	}
	return h;
}

//2D coordinates, and a world seed
uint32_t coordhash(uint32_t seed, uint32_t x, uint32_t y) {
	//non-comutative hash
	return uinthash(uinthash(x)) ^ uinthash(y) ^ seed;
}
