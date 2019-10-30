#include <string>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;
bool CanFormPalindrome(const string& s) {
	unordered_set<char> chars;

	for (auto& c : s) {
		auto it = chars.find(c);
		if (it == chars.end())
			chars.insert(c);
		else
			chars.erase(it);
	}

	return chars.size() <= 1;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
		"is_string_permutable_to_palindrome.tsv",
		&CanFormPalindrome, DefaultComparator{}, param_names);
}