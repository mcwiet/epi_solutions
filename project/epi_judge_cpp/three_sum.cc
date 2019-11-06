#include <vector>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;

bool HasThreeSum(vector<int> A, int t) {
	unordered_set<int> nums(A.begin(), A.end());
	int count = 0;

	for (auto i = nums.begin(); i != nums.end(); ++i) {
		for (auto j = i; j != nums.end(); ++j) {
			if (nums.find(t - (*i + *j)) != nums.end())
				++count;
		}
	}

	return count;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "t" };
	return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
		DefaultComparator{}, param_names);
}