#include <vector>
#include <queue>
#include <functional>
#include "test_framework/generic_test.h"
using std::vector;
using std::priority_queue;
using std::greater;
struct ArrayTracker {
	bool operator>(const ArrayTracker& other) const {
		return *current > * other.current;
	}

	vector<int>::const_iterator current;
	vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
	priority_queue<ArrayTracker, vector<ArrayTracker>, greater<>> heap;

	for (auto& arr : sorted_arrays) {
		if (!arr.empty())
			heap.emplace(ArrayTracker{ arr.cbegin(), arr.cend() });
	}

	vector<int> ret;
	while (!heap.empty()) {
		auto smallest = heap.top();
		ret.emplace_back(*smallest.current);
		if (next(smallest.current) != smallest.end)
			heap.emplace(ArrayTracker{ next(smallest.current), smallest.end });
		heap.pop();
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