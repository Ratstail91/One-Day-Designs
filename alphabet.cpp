/* This sorted a sealed pool of MTG cards in this format by alphabetical order:
1x Black Lotus
3x Force of Will
1x Abzan Advantage
...and so on
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

struct Entry {
	int count;
	std::string name;

	//for sorting
	bool operator<(Entry const& rhs) const {
		int len = std::max(name.length(), rhs.name.length());
		int cmp = strncmp(name.c_str(), rhs.name.c_str(), len);
		return cmp < 0; //we only want the result of '<'
	}
};

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "USAGE: " << argv[0] << " INPUT OUTPUT" << std::endl;
		return 0;
	}

	std::ifstream is(argv[1]);

	if (!is.is_open()) {
		std::cerr << "Failed to open " << argv[1] << std::endl;
		return 1;
	}

	//container with built-in sorting
	std::set<Entry> data;

	//variables for reading
	std::string line;
	char namebuf[256];
	Entry newEntry;
	int ret;

	//input
	while(!is.eof()) {
		getline(is, line);
		ret = sscanf(line.c_str(), "%dx %[^\0]s\0", &newEntry.count, namebuf);
		newEntry.name = namebuf;

		if (ret != 2) {
			std::cerr << "Failed to interpret input, exiting" << std::endl;
			return 1;
		}

		data.insert(newEntry);
	}

	is.close();

	//output
	std::ofstream os(argv[2]);

	if (!os.is_open()) {
		std::cerr << "Failed to open " << argv[1] << std::endl;
		return 1;
	}

	std::for_each(data.begin(), data.end(), [&os](Entry const& e) {
		os << e.count << "x " << e.name << std::endl;
	});

	os.close();

	std::cout << "Finished " << argv[0] << std::endl;

	return 0;
}
