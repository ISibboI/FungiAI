#include "strings.hpp"
#include "game/cards/card_information.hpp"

#include <sstream>

using namespace std;

string Strings::str(const vector<uint8_t>& v) {
	stringstream ss;
	ss << "[";

	for (auto id = v.begin(); id != v.end(); id++) {
		if (id != v.begin()) {
			ss << ", ";
		}

		ss << CardInformation::get_card(*id).name;
	}

	ss << "]";
	return ss.str();
}