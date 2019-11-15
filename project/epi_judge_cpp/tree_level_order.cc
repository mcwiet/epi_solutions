#include <memory>
#include <vector>
#include <queue>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::queue;
vector<vector<int>> BinaryTreeDepthOrder(
	const unique_ptr<BinaryTreeNode<int>>& tree) {
	vector<vector<int>> vals;
	queue<BinaryTreeNode<int>*> q;

	if (tree == nullptr)
		return vals;

	q.push(tree.get());
	vals.emplace_back(vector<int>());
	int nodes_current_level = 1;
	int nodes_next_level = 0;

	while (!q.empty()) {
		auto node = q.front();
		vals.back().emplace_back(node->data);
		q.pop();
		--nodes_current_level;
		if (node->left != nullptr) {
			q.push(node->left.get());
			++nodes_next_level;
		}
		if (node->right != nullptr) {
			q.push(node->right.get());
			++nodes_next_level;
		}

		if (nodes_current_level == 0) {
			if (nodes_next_level == 0)
				break;
			nodes_current_level = nodes_next_level;
			nodes_next_level = 0;
			vals.emplace_back(vector<int>());
		}
	}

	return vals;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
		&BinaryTreeDepthOrder, DefaultComparator{},
		param_names);
}