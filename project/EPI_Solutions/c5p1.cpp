#include "c5_problems.h"
#include <vector>
#include <iostream>

namespace Chapter5 {
	void Problem1::Partition(std::vector<Color>&& a, int pivot_index) {
		Color piv = a[pivot_index];

		std::cout << "Pivot = " << piv << std::endl;
		std::cout << "Before: ";
		for (auto col : a)
			std::cout << col << " ";
		std::cout << std::endl;

		int small = 0;
		for (unsigned i = 0; i < a.size(); ++i) {
			if (a[i] < piv)
				std::swap(a[small++], a[i]);
		}
		int large = a.size() - 1;
		for (unsigned i = a.size() - 1; i >= small; --i) {
			if (a[i] > piv)
				std::swap(a[large--], a[i]);
		}
		std::cout << "After: ";
		for (auto col : a)
			std::cout << col << " ";
		std::cout << std::endl;
	}
};