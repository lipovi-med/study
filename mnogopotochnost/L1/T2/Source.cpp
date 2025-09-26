#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
using namespace std;

vector<int> vec1(1000000);
vector<int> vec2(1000000);
vector<int> vec3(1000000);

void sum(const int start,const int end) {
	for (int i = start; i <= end; i++) {
		vec3[i] = vec2[i] + vec1[i];
	}
}

auto sum_thr(int vol, int thrnum) {
	auto start = chrono::system_clock::now();
	int add = vol / thrnum;
	vector<thread> threads;
	for (int i = 0; i < thrnum; i++) {
		threads.emplace_back(sum, (i * add), ((i + 1) * add - 1));
	}
	for (auto& t : threads) {
		t.join();
	}
	auto end = chrono::system_clock::now();
	chrono::duration<double, milli> time = end - start;
	return time.count();
}

int main()
{
	cout << "#threads: " << thread::hardware_concurrency() << endl;


	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(-10000, 10000);
	for (auto& x : vec1) { x = dis(gen); }
	for (auto& x : vec2) { x = dis(gen); }

	cout << "\t\t" << "1000\t\t\t" << "10000\t\t\t" << "100000\t\t\t" << "1000000\t\t\t" << endl;
	cout << "1 thr\t\t" << sum_thr(1000, 1) << "ms\t\t" << sum_thr(10000, 1) << "ms\t\t" << sum_thr(100000, 1) << "ms\t\t" << sum_thr(1000000, 1) << "ms\t\t" << endl;
	cout << "2 thr\t\t" << sum_thr(1000, 2) << "ms\t\t" << sum_thr(10000, 2) << "ms\t\t" << sum_thr(100000, 2) << "ms\t\t" << sum_thr(1000000, 2) << "ms\t\t" << endl;
	cout << "4 thr\t\t" << sum_thr(1000, 4) << "ms\t\t" << sum_thr(10000, 4) << "ms\t\t" << sum_thr(100000, 4) << "ms\t\t" << sum_thr(1000000, 4) << "ms\t\t" << endl;
	cout << "8 thr\t\t" << sum_thr(1000, 8) << "ms\t\t" << sum_thr(10000, 8) << "ms\t\t" << sum_thr(100000, 8) << "ms\t\t" << sum_thr(1000000, 8) << "ms\t\t" << endl;
	cout << "16 thr\t\t" << sum_thr(1000, 16) << "ms\t\t" << sum_thr(10000, 16) << "ms\t\t" << sum_thr(100000, 16) << "ms\t\t" << sum_thr(1000000, 16) << "ms\t\t" << endl;

}