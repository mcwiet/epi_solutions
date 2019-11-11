#include <thread>
#include <mutex>
#include <iostream>
using namespace std;

bool even_ready = false;
bool odd_ready = false;
mutex mtx;
condition_variable cv;
int the_count = 0;
int the_goal = 100;

void EvenPrinter() {
	while (1) {
		unique_lock<mutex> lck(mtx);
		while (!even_ready) cv.wait(lck);

		cout << the_count << ", ";
		++the_count;

		even_ready = false;
		odd_ready = true;

		if (the_count >= the_goal) break;
		cv.notify_one();
	}
	cv.notify_one();
}

void OddPrinter() {
	while (1) {
		unique_lock<mutex> lck(mtx);
		while (!odd_ready) cv.wait(lck);

		cout << the_count << ", ";
		++the_count;

		even_ready = true;
		odd_ready = false;

		if (the_count >= the_goal) break;
		cv.notify_one();
	}
	cv.notify_one();
}

int main() {
	thread even(EvenPrinter);
	thread odd(OddPrinter);

	unique_lock<mutex> lck(mutex);
	even_ready = true;

	even.join();
	odd.join();
	return 0;
}