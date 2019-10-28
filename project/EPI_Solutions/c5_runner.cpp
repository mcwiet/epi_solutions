#include "c5_problems.h"

namespace Chapter5 {
	void Run() {
		Problem1().PrintName();
		Problem1().Partition(std::vector<Color>{ Color::White, Color::Red, Color::White, Color::Blue, Color::Red, Color::White, Color::Blue, Color::Blue, Color::White }, 0);
	}
}