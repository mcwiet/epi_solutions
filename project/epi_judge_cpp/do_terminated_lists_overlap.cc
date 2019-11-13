#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
	shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
	int l0_length = 0, l1_length = 0;
	auto l0_temp = l0, l1_temp = l1;

	while (l0_temp != nullptr) {
		l0_temp = l0_temp->next;
		++l0_length;
	}
	while (l1_temp != nullptr) {
		l1_temp = l1_temp->next;
		++l1_length;
	}

	auto long_list = (l0_length > l1_length) ? l0 : l1;
	auto short_list = (l0_length > l1_length) ? l1 : l0;
	auto long_length = std::max(l0_length, l1_length);
	auto short_length = std::min(l0_length, l1_length);

	while (long_length > short_length) {
		long_list = long_list->next;
		--long_length;
	}

	while (long_list != nullptr) {
		if (long_list == short_list)
			return long_list;
		long_list = long_list->next;
		short_list = short_list->next;
	}
	return nullptr;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
	shared_ptr<ListNode<int>> l0,
	shared_ptr<ListNode<int>> l1,
	shared_ptr<ListNode<int>> common) {
	if (common) {
		if (l0) {
			auto i = l0;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		}
		else {
			l0 = common;
		}

		if (l1) {
			auto i = l1;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		}
		else {
			l1 = common;
		}
	}

	auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

	if (result != common) {
		throw TestFailure("Invalid result");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "l0", "l1", "common" };
	return GenericTestMain(
		args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
		&OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}