/* Copyright: (c) Kayne Ruse 2013-2015
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

/* DOCUMENTATION

This is a rough format converter for pucatrade. Since pucatrade's "import cards"
system is tempremental, I wrote this to deal with it. Note that this was
tailored for my own personal collection, so most sets are not covered (but can
be added below), and that there is no explicit foil-handling or special edition
handling at the present time.

Compiles under C++11

Expected source format:

	1x Shivan Dragon (ORI)
	1x Urborg, Tomb of Yawgmoth (M15)
	1x Chromatic Lantern (RTR)

Intended output format:

	1x Shivan Dragon Magic Origins
	1x Urborg, Tomb of Yawgmoth Magic 2015 Core Set
	1x Chromatic Lantern Return to Ravnica

*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <stdexcept>
#include <string>

typedef std::map<std::string, std::string> table_t;

const table_t conversions = {
	//core sets
	{"(ORI)", "Magic Origins"},
	{"(M15)", "Magic 2015 Core Set"},
	{"(M14)", "Magic 2014 Core Set"},
	{"(M13)", "Magic 2013"},
	{"(M12)", "Magic 2012"},
	{"(M11)", "Magic 2011"},
	{"(M10)", "Magic 2010"},

	//blocks
	{"(BFZ)", "Battle for Zendikar"},
	{"(DTK)", "Dragons of Tarkir"},
	{"(FRF)", "Fate Reforged"},
	{"(KTK)", "Khans of Tarkir"},
	{"(JOU)", "Journey into Nyx"},
	{"(BNG)", "Born of the Gods"},
	{"(THS)", "Theros"},
	{"(DGM)", "Dragon's Maze"},
	{"(GTC)", "Gatecrash"},
	{"(RTR)", "Return to Ravnica"},
	{"(AVR)", "Avacyn Restored"},
	{"(DKA)", "Dark Ascension"},
	{"(ISD)", "Innistrad"},

	{"(WWK)", "Worldwake"},

	//supplements
//	{"(MMA)", "Modern Masters"},
	{"(MM2)", "Modern Masters 2015"},
	{"(C14)", "Commander 2014"},
	{"(DDJ)", "Duel Decks: Izzet vs. Golgari"},
};

//compare two strings starting from the end
//returns similar to strncmp
int rstrncmp(std::string lhs, std::string rhs, int rnum) {
	auto lit = lhs.rbegin();
	auto rit = rhs.rbegin();
	int ret = 0;

	while (rnum-- > 0) {
		if (*lit < *rit) {
			ret = -1;
			break;
		}
		if (*lit > *rit) {
			ret = 1;
			break;
		}

		//check if the "end" of the string has been reached
		if (lit++ == lhs.rend()) {
			rnum = -1;
			ret += -1;
		}
		if (rit++ == rhs.rend()) {
			rnum = -1;
			ret += 1;
		}
	}

	//rnum ran out or was set to -1
	return ret;
}

int main(int argc, char* argv[]) {
	//usage check
	if (argc != 3) {
		std::cout << "USAGE: " << argv[0] << " SOURCE DEST" << std::endl;
		return 0;
	}

	//open the files
	std::fstream is(argv[1], std::fstream::in);

	if (!is.is_open()) {
		std::cerr << "Failed to open " << argv[1] << std::endl;
		return 1;
	}

	std::fstream os(argv[2], std::fstream::out);

	if (!os.is_open()) {
		std::cerr << "Failed to open " << argv[2] << std::endl;
		is.close();
		return 1;
	}

	//read in
	std::list<std::string> inputList;
	std::string tmp;
	while(!is.eof()) {
		getline(is, tmp);
		inputList.push_back(tmp);
	}

	//convert
	std::for_each(inputList.begin(), inputList.end(), [conversions](std::string& str) {
		//compare the end of the given string to the conversion keys
		for (auto const& it : conversions) {
			if (rstrncmp(it.first, str, it.first.size()) == 0) {
				//rewrite the end
				str = str.substr(0, str.size() - it.first.size());
				str += it.second;
				return;
			}
		}
		std::cout << "WARNING: Unknown card: " << str << std::endl;
	});

	//write the output
	for (auto& it : inputList) {
		os << it << std::endl;
	}

	//close the files
	is.close();
	os.close();

	return 0;
}
