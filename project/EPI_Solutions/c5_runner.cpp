#include "c5_problems.h"

namespace Chapter5 {
	void Run() {
		Problem1().Partition(std::vector<Color>{ Color::White, Color::Red, Color::White, Color::Blue, Color::Red, Color::White, Color::Blue, Color::Blue, Color::White }, 0);
		Problem6().BuySellStockOnce(std::vector<int>{310, 315, 275, 295, 260, 270, 290, 230, 255, 250});
	}
}