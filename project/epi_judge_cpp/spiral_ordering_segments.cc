#include <vector>
#include <array>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(vector<vector<int>> mat) {
	if (mat.empty() || mat[0].empty())
		return {};
	vector<int> vec(mat.size() * mat.size(), -1);
	std::pair<int, int> d_mods[] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int d = 0, x = 0, y = 0;

	for (int i = 0; i < vec.size(); ++i) {
		vec[i] = mat[x][y];
		mat[x][y] = -1;
		int x2 = x + d_mods[d].first;
		int y2 = y + d_mods[d].second;
		if (x2 < 0 || x2 >= mat.size() || y2 < 0 || y2 >= mat.size() || mat[x2][y2] == -1) {
			d = (++d) % 4;
			x2 = x + d_mods[d].first;
			y2 = y + d_mods[d].second;
		}
		x = x2;
		y = y2;
	}

	return vec;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "square_matrix" };
	return GenericTestMain(args, "spiral_ordering_segments.cc",
		"spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
		DefaultComparator{}, param_names);
}