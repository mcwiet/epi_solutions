#include <array>
#include <stack>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;

void HanoiHelper(int num_rings, vector<vector<int>>& moves, array<stack<int>, kNumPegs>& towers, int from_tower, int to_tower, int temp_tower) {
	if (num_rings <= 0)
		return;
	HanoiHelper(num_rings - 1, moves, towers, from_tower, temp_tower, to_tower);
	towers[to_tower].push(towers[from_tower].top());
	towers[from_tower].pop();
	moves.emplace_back(vector<int>{from_tower, to_tower});
	HanoiHelper(num_rings - 1, moves, towers, temp_tower, to_tower, from_tower);
}

vector<vector<int>> ComputeTowerHanoi(int num_rings) {
	array<stack<int>, kNumPegs> towers;
	vector<vector<int>> ret;

	for (int i = 0; i < num_rings; ++i)
		towers[0].emplace(i);

	HanoiHelper(num_rings, ret, towers, 0, 1, 2);

	return ret;
}
void ComputeTowerHanoiWrapper(TimedExecutor& executor, int num_rings) {
	array<stack<int>, kNumPegs> pegs;
	for (int i = num_rings; i >= 1; --i) {
		pegs[0].push(i);
	}

	vector<vector<int>> result =
		executor.Run([&] { return ComputeTowerHanoi(num_rings); });

	for (const vector<int>& operation : result) {
		int from_peg = operation[0], to_peg = operation[1];
		if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
			throw TestFailure("Illegal move from " +
				std::to_string(pegs[from_peg].top()) + " to " +
				std::to_string(pegs[to_peg].top()));
		}
		pegs[to_peg].push(pegs[from_peg].top());
		pegs[from_peg].pop();
	}
	array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
	for (int i = num_rings; i >= 1; --i) {
		expected_pegs1[1].push(i);
	}
	for (int i = num_rings; i >= 1; --i) {
		expected_pegs2[2].push(i);
	}
	if (pegs != expected_pegs1 && pegs != expected_pegs2) {
		throw TestFailure("Pegs doesn't place in the right configuration");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "num_rings" };
	return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
		&ComputeTowerHanoiWrapper, DefaultComparator{},
		param_names);
}