#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <numeric>
using namespace std;

// Минимальный размер блока (ниже которого выполняем последовательно)
constexpr size_t MIN_BLOCK_SIZE = 1000;

// Параллельный for_each
template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
    auto length = distance(first, last);

    if (length <= MIN_BLOCK_SIZE) {
        // маленький диапазон обрабатываем последовательно
        for_each(first, last, f);
    }
    else {
        // делим диапазон на две части
        Iterator mid = first;
        advance(mid, length / 2);

        // запускаем левую часть в отдельной задаче
        auto handle = async(launch::async,
            parallel_for_each<Iterator, Func>,
            first, mid, f);

        // обрабатываем правую часть в текущем потоке
        parallel_for_each(mid, last, f);

        // ждём левую задачу
        handle.get();
    }
}

int main() {
    vector<int> data(1000000);
    iota(data.begin(), data.end(), 1);

    parallel_for_each(data.begin(), data.end(), [](int& x) { x += 1; });

    // Проверка
    cout << "First 10 elements after parallel_for_each: ";
    for (int i = 0; i < 10; i++) cout << data[i] << " ";
    cout << endl;
}
