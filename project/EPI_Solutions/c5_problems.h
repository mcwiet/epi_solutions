#pragma once

#include "Problem.h"
#include <vector>

namespace Chapter5 {
	enum Color { Red, White, Blue };

	struct Problem1 : public Problem {
		Problem1() : Problem("Chapter 5 Problem 1") {};
		void Partition(std::vector<Color>&& a, int pivot_index);
	};

	struct Problem6 : public Problem {
		Problem6() : Problem("Chapter 5 Problem 6") {};
		void BuySellStockOnce(std::vector<int>&& stocks);
	};
}