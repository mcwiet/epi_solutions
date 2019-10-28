#include "c5_problems.h"
#include <algorithm>
#include <iostream>

namespace Chapter5 {
	void Problem6::BuySellStockOnce(std::vector<int>&& stocks) {
		std::cout << "Stocks: ";
		for (auto stock : stocks)
			std::cout << stock << " ";
		std::cout << std::endl;

		int best_prof = 0;
		if (stocks.size() != 0) {
			int cur_low = stocks[0];
			for (auto stock : stocks) {
				best_prof = std::max(best_prof, stock - cur_low);
				cur_low = std::min(cur_low, stock);
			}
		}

		std::cout << "Best profit = " << best_prof << std::endl;
	}
}