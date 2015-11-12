/* Copyright: (c) Kayne Ruse 2015
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/

/* DOCS: filter a list

Given two lists A and B, find all elements in B that are not present in A.

I used this to filter "maybes" from a list of cards.
Doesn't handle formatting or duplication of any kind.

g++ -std=c++11 -o filter filter.cpp
./filter decklist filterlist output

*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "USAGE: " << argv[0] << " LIST MAYBE OUTPUT" << std::endl;
		return 1;
	}

	//list
	std::ifstream inList(argv[1]);
	std::vector<std::string> decklist;

	while(!inList.eof()) {
		std::string buffer;
		getline(inList, buffer);
		decklist.push_back(buffer);
	}

	inList.close();

	//filter
	std::ifstream inFilter(argv[2]);
	std::vector<std::string> filter;

	while(!inFilter.eof()) {
		std::string buffer;
		getline(inFilter, buffer);
		filter.push_back(buffer);
	}

	inFilter.close();

	//remove_if() didn't work
	std::ofstream os(argv[3]);

	std::for_each(filter.begin(), filter.end(), [&](std::string& str) {
		for (auto& it : decklist) {
			if ( !strcmp(it.c_str(), str.c_str()) )
				return;
		}
		os << str << std::endl;
	});

	os.close();

	return 0;
}
