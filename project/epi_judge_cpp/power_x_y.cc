#include "test_framework/generic_test.h"
double Power(double x, int y) {
	if (y == 0)
		return 1.0;

	double ret = 1;
	double temp = x;
	int exp = 1;

	while (y != 0) {
		while (y >= (2 * exp)) {
			if (y < 0)
				temp /= temp;
			else
				temp *= temp;
			exp *= 2;
		}
		if (y < 0) {
			ret /= temp;
			y += exp;
		}
		else {
			ret *= temp;
			y -= exp;
		}
		temp = x;
		exp = 1;
	}
	return ret;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x", "y" };
	return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
		DefaultComparator{}, param_names);
}