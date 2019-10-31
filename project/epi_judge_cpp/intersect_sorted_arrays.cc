#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& a,
	const vector<int>& b)
{
	auto ita = a.begin();
	auto itb = b.begin();
	vector<int> intersections;

	while ((ita != a.end()) && (itb != b.end())) {
		if (*ita < *itb)
			++ita;
		else if (*itb < *ita)
			++itb;
		else if (*ita == *itb) {
			int num = *ita;
			intersections.push_back(num);
			while ((ita != a.end()) && (*ita == num))
				++ita;
			while ((itb != b.end()) && (*itb == num))
				++itb;
		}
	}

	return intersections;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "B" };
	return GenericTestMain(
		args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
		&IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}