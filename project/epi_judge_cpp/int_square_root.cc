#include "test_framework/generic_test.h"

int SquareRoot(int k) {
	int upper = k, lower = 0;
	long long mid = 0;

	while (lower <= upper) {
		mid = lower + (upper - lower) / 2;
		long long mid_sqr = mid * mid;
		if (mid_sqr <= k)
			lower = mid + 1;
		else
			upper = mid - 1;
	}

	return lower - 1;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "k" };
	return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
		&SquareRoot, DefaultComparator{}, param_names);
}