#include <iterator>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
	int num_a = 0;
	int write = 0;
	for (int i = 0; i < size; ++i) {
		if (s[i] != 'b')
			s[write++] = s[i];
		if (s[i] == 'a')
			++num_a;
	}

	int current = write - 1;
	write = write + num_a - 1;
	int final_index = write + 1;
	while (current >= 0) {
		if (s[current] == 'a') {
			s[write--] = 'd';
			s[write--] = 'd';
		}
		else {
			s[write--] = s[current];
		}
		--current;
	}

	return final_index;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
	const vector<string>& s) {
	std::vector<char> s_copy(s.size(), '\0');
	for (int i = 0; i < s.size(); ++i) {
		if (!s[i].empty()) {
			s_copy[i] = s[i][0];
		}
	}

	int res_size =
		executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

	vector<string> result;
	for (int i = 0; i < res_size; ++i) {
		result.emplace_back(string(1, s_copy[i]));
	}
	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "size", "s" };
	return GenericTestMain(args, "replace_and_remove.cc",
		"replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
		DefaultComparator{}, param_names);
}