#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>

unsigned fnv_hash_1a_32(void *key, int len) {
	unsigned char *p = static_cast<unsigned char*>(key);
	unsigned h = 0x811c9dc5;
	for (int i = 0; i < len; i++) {
		h = (h ^ p[i]) * 0x01000193;
	}
	return h;
}

struct Pack {
	Pack() {
		nonce = 0;
		memset(data, 0, 100);
	}
	unsigned nonce;
	char data[100];
};

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << " STRING HARDNESS" << std::endl;
		return 1;
	}

	//input
	Pack p;
	memcpy(p.data, argv[1], strlen(argv[1]));
	unsigned hardness = atoi(argv[2]);

	//check bounds
	if (hardness < 1 || hardness > 32) {
		std::cout << "HARDNESS must be between 1 and 32" << std::endl;
		return 1;
	}

	//find
	unsigned h;
	do {
		h = fnv_hash_1a_32(static_cast<void*>(&p), sizeof(p));
		std::cout << "Trying: 0x" << std::hex << std::setw(8) << std::setfill('0') << std::right << h << " (" << p.nonce << ")" << "\r";
		p.nonce++;
	} while (h > (0x1 << (32 - hardness)) && p.nonce);
	std::cout << std::endl;

	//finish
	if (p.nonce) {
		std::cout << "Final:  0x" << std::hex << std::setw(8) << std::setfill('0') << std::right << h << std::endl;
		return 0;
	}
	else {
		std::cout << "Failed to find a hash" << std::endl;
		return 2;
	}
}