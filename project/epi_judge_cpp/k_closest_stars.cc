#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <functional>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"
using std::vector;
using std::priority_queue;
using std::function;

struct Star {
	bool operator<(const Star& that) const {
		return Distance() < that.Distance();
	}

	double Distance() const { return sqrt(x * x + y * y + z * z); }

	double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
	const vector<Star>::const_iterator& stars_end, int k) {
	priority_queue<Star> max_heap;

	while (stars_begin != stars_end) {
		auto star = *stars_begin;
		max_heap.push(*stars_begin);
		if (max_heap.size() > k)
			max_heap.pop();
		++stars_begin;
	}

	vector<Star> ret;
	while (!max_heap.empty()) {
		ret.push_back(max_heap.top());
		max_heap.pop();
	}

	return ret;
}
template <>
struct SerializationTraits<Star> : UserSerTraits<Star, double, double, double> {
};

std::ostream& operator<<(std::ostream& out, const Star& s) {
	return out << s.Distance();
}

bool Comp(const vector<double>& expected, vector<Star> output) {
	if (output.size() != expected.size()) {
		return false;
	}

	std::sort(begin(output), end(output));

	for (int i = 0; i < output.size(); ++i) {
		if (!DefaultComparator()(output[i].Distance(), expected[i])) {
			return false;
		}
	}
	return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star>& stars, int k) {
	return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "stars", "k" };
	return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
		&FindClosestKStarsWrapper, &Comp, param_names);
}