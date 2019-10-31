#include <memory>
#include <limits>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool IsNodeValid(const unique_ptr<BinaryTreeNode<int>>& node, int low, int high) {
	if (node == nullptr)
		return true;
	else if ((node->data < low) || (node->data > high))
		return false;

	return IsNodeValid(node->left, low, node->data) && IsNodeValid(node->right, node->data, high);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
	return IsNodeValid(tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
		&IsBinaryTreeBST, DefaultComparator{}, param_names);
}