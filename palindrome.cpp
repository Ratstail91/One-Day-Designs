#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " INPUTFILE OUTPUTFILE" << endl;
		return 0;
	}

	if (!strcmp(argv[1], argv[2])) {
		cerr << "Error: Input and output files must not be the same file" << endl;
		return 1;
	}

	ifstream is(argv[1]);

	if (!is.is_open()) {
		cerr << "Failed to open the input file: " << argv[1] << endl;
		return 1;
	}

	ofstream os(argv[2]);

	if (!os.is_open()) {
		is.close();
		cerr << "Failed to open the output file: " << argv[2] << endl;
		return 1;
	}

	os << "#define foo fidne#" << endl;

	vector<string> store;

	while(!is.eof()) {
		string s;
		getline(is, s);
		store.push_back(s);
		os << s << endl;
	}

	is.close();

	os << "#if 0" << endl << "0 fi#" << endl;

	for (vector<string>::reverse_iterator it = store.rbegin(); it != store.rend(); it++) {
		for (string::reverse_iterator sit = it->rbegin(); sit != it->rend(); sit++) {
			os << *sit;
		}
		store.pop_back();
		if (store.size()) {
			os << endl;
		}
	}

	os << endl << "#endif oof enifed#";

	os.close();

	return 0;
}