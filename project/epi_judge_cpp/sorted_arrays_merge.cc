#include <vector>
#include <queue>
#include <functional>
#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
	int vals = 0;
	for (auto& vec : sorted_arrays) {
		for (auto& num : vec)
			++vals;
	}

	priority_queue<int, vector<int>, std::greater<int>> nums(0, vals);
	for (auto& vec : sorted_arrays) {
		for (auto& num : vec)
			nums.emplace(num);
	}
	vector<int> ret;
	while (nums.size()) {
		ret.push_back(nums.top());
		nums.pop();
	}

	return ret;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "sorted_arrays" };
	return GenericTestMain(args, "sorted_arrays_merge.cc",
		"sorted_arrays_merge.tsv", &MergeSortedArrays,
		DefaultComparator{}, param_names);
}