#pragma once

#include "IProblem.h"
#include <vector>

namespace Chapter5 {
	enum Color { Red, White, Blue };

	class Problem1 : public IProblem {
	public:
		Problem1() : IProblem("Chapter 5 Problem 1") {};
		void Partition(std::vector<Color>&& a, int pivot_index);
	};
}