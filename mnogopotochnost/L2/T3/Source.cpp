#include <iostream>
#include <thread>
#include <mutex>
#include <utility>   // std::swap
using namespace std;

class Data {
public:
    int value;
    mutable mutex mtx;   // mutable — чтобы можно было блокировать в const-функциях

    Data(int v = 0) : value(v) {}
};

// с использованием std::lock
void swap_lock(Data& a, Data& b) {
    if (&a == &b) return;  // защита от самоперемены

    // Захватываем оба мьютекса, избегаем deadlock
    lock(a.mtx, b.mtx);
    lock_guard<mutex> lg1(a.mtx, adopt_lock);
    lock_guard<mutex> lg2(b.mtx, adopt_lock);

    std::swap(a.value, b.value);
}

// с использованием std::scoped_lock (C++17)
void swap_scoped(Data& a, Data& b) {
    if (&a == &b) return;

    scoped_lock lock(a.mtx, b.mtx);
    std::swap(a.value, b.value);
}

// с использованием std::unique_lock
void swap_unique(Data& a, Data& b) {
    if (&a == &b) return;

    unique_lock<mutex> ul1(a.mtx, defer_lock);
    unique_lock<mutex> ul2(b.mtx, defer_lock);
    lock(ul1, ul2);   // безопасно блокируем оба

    std::swap(a.value, b.value);
}

int main() {
    Data d1(10), d2(20);

    cout << "Before swap: d1=" << d1.value << ", d2=" << d2.value << endl;

    swap_lock(d1, d2);
    cout << "After swap_lock: d1=" << d1.value << ", d2=" << d2.value << endl;

    swap_scoped(d1, d2);
    cout << "After swap_scoped: d1=" << d1.value << ", d2=" << d2.value << endl;

    swap_unique(d1, d2);
    cout << "After swap_unique: d1=" << d1.value << ", d2=" << d2.value << endl;

    return 0;
}
