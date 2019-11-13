#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> l, int start,
	int finish) {
	auto head = make_shared<ListNode<int>>(0, l);
	auto sub_head = head;

	int i = 0;
	while (++i < start)
		sub_head = sub_head->next;

	auto sub_it = sub_head->next;
	while (i++ < finish) {
		auto temp = sub_it->next;
		sub_it->next = temp->next;
		temp->next = sub_head->next;
		sub_head->next = temp;
	}

	return head->next;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L", "start", "finish" };
	return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
		&ReverseSublist, DefaultComparator{}, param_names);
}