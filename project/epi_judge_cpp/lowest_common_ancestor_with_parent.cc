#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int getDepth(BinaryTreeNode<int>* node) {
	int depth = -1;
	while (node) {
		++depth;
		node = node->parent;
	}

	return depth;
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
	const unique_ptr<BinaryTreeNode<int>>& node1) {
	if (node0 == nullptr || node1 == nullptr)
		return nullptr;
	// Calculate depth of each node
	// Re-wind deepest node until nodes are at same depth
	// Check each nodes' parent; if same, break. Otherwise unwind each node once

	BinaryTreeNode<int>* n0 = node0.get();
	BinaryTreeNode<int>* n1 = node1.get();
	int depth0 = getDepth(n0);
	int depth1 = getDepth(n1);

	int max_depth = std::max(depth0, depth1);
	int min_depth = std::min(depth0, depth1);
	BinaryTreeNode<int>* deep_tree = (depth0 > depth1) ? node0.get() : node1.get();
	BinaryTreeNode<int>* shallow_tree = (depth0 > depth1) ? node1.get() : node0.get();

	while (max_depth != min_depth) {
		deep_tree = deep_tree->parent;
		--max_depth;
	}

	BinaryTreeNode<int>* common = nullptr;

	while (deep_tree != nullptr && shallow_tree != nullptr) {
		if (deep_tree == shallow_tree) {
			common = deep_tree;
			break;
		}
		else {
			deep_tree = deep_tree->parent;
			shallow_tree = shallow_tree->parent;
		}
	}

	return common;
}

int LcaWrapper(TimedExecutor& executor,
	const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
	int key1) {
	const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
	const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

	auto result = executor.Run([&] { return LCA(node0, node1); });

	if (!result) {
		throw TestFailure("Result can not be nullptr");
	}
	return result->data;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "tree", "key0", "key1" };
	return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
		"lowest_common_ancestor.tsv", &LcaWrapper,
		DefaultComparator{}, param_names);
}