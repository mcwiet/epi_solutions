#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
	sort(A.begin(), A.end());

	for (auto current : A) {
		int low = 0;
		int high = A.size() - 1;
		while (low <= high) {
			int diff = (A[low] + A[high]) - (t - current);
			if (diff == 0)
				return true;
			else if (diff < 0)
				++low;
			else
				--high;
		}
	}

	return false;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "t" };
	return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
		DefaultComparator{}, param_names);
}