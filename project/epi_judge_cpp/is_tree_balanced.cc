#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (!tree)
		return true;
	if ((!tree->left) && (!tree->right))
		return true;
	else if ((!tree->left) && ((tree->right->left) || (tree->right->right)))
		return false;
	else if ((!tree->right) && ((tree->left->left) || (tree->left->right)))
		return false;
	else
		return IsBalanced(tree->left) && IsBalanced(tree->right);
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
		&IsBalanced, DefaultComparator{}, param_names);
}