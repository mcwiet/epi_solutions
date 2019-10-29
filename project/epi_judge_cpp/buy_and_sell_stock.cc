#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
	double best_prof = 0.0;
	if (prices.size() != 0) {
		double cur_low = prices[0];
		for (auto stock : prices) {
			best_prof = std::max(best_prof, stock - cur_low);
			cur_low = std::min(cur_low, stock);
		}
	}
	return best_prof;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "prices" };
	return GenericTestMain(args, "buy_and_sell_stock.cc",
		"buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
		DefaultComparator{}, param_names);
}