#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
using namespace std;

void in(atomic<unsigned int>& q, unsigned int MAX) {
    do {
        this_thread::sleep_for(1s);
        unsigned int old = q.fetch_add(1, memory_order_relaxed) + 1;
        cout << "\rV ocheredi: " << old << flush;
    } while (q.load(memory_order_relaxed) < MAX);
}

void out(atomic<unsigned int>& q) {
    this_thread::sleep_for(1s); // старт задержкой, чтобы очередь успела наполниться
    do {
        this_thread::sleep_for(2s);
        unsigned int old = q.fetch_sub(1, memory_order_relaxed) - 1;
        cout << "\rV ocheredi: " << old << " " << flush;
    } while (q.load(memory_order_relaxed) > 0);
}

int main() {
    cout << "#threads: " << thread::hardware_concurrency() << endl;

    atomic<unsigned int> queue{ 0 };
    unsigned int queueMAX;
    cout << "Max ochered: ";
    cin >> queueMAX;

    thread t1(in, ref(queue), queueMAX);
    thread t2(out, ref(queue));

    t1.join();
    t2.join();
}
