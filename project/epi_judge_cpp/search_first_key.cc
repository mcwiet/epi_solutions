#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& a, int k) {
	int u = a.size() - 1;
	int l = 0;
	int i = -1;

	// Initial BST
	while (l <= u) {
		int m = l + (u - l) / 2;
		if (k < a[m])
			u = m - 1;
		else if (k > a[m])
			l = m + 1;
		else {
			u = m - 1;
			i = m;
		}
	}

	return i;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "k" };
	return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
		&SearchFirstOfK, DefaultComparator{}, param_names);
}