#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

	void in(unsigned int& q, unsigned int MAX)	// прибавляет очередь
	{
		do {
			this_thread::sleep_for(1s);
			q++;
			cout << "\r" << "V ocheredi: " << q;
		} while (q < MAX);
	}

	void out(unsigned int& q)	// убавляет очередь						
	{
		this_thread::sleep_for(1s);
		do {
			this_thread::sleep_for(2s);
			q--;
			cout << "\r" << "V ocheredi: " << q << " ";
		} while (q > 0);
	}

int main()
{
	cout << "#threads: " << thread::hardware_concurrency() << endl;

	unsigned int queue = 0;
	unsigned int queueMAX;
	cout << "Max ochered: ";
	cin >> queueMAX;

	thread t1(in, ref(queue), queueMAX);
	thread t2(out, ref(queue));

	t1.join();
	t2.join();
}