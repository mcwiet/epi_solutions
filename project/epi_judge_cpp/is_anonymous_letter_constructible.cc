#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
	const string& magazine_text) {
	unordered_map<char, unsigned> chars;

	for (auto& c : letter_text) {
		auto it = chars.find(c);
		if (it == chars.end())
			chars.emplace(c, 1);
		else
			++(it->second);
	}

	for (auto& c : magazine_text) {
		auto it = chars.find(c);
		if (it != chars.end()) {
			--it->second;
			if (it->second <= 0) {
				chars.erase(it);
				if (chars.empty())
					break;
			}
		}
	}

	return chars.empty();
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "letter_text", "magazine_text" };
	return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
		"is_anonymous_letter_constructible.tsv",
		&IsLetterConstructibleFromMagazine,
		DefaultComparator{}, param_names);
}