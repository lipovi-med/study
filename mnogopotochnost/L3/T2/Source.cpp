#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <numeric>
using namespace std;

// ����������� ������ ����� (���� �������� ��������� ���������������)
constexpr size_t MIN_BLOCK_SIZE = 1000;

// ������������ for_each
template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
    auto length = distance(first, last);

    if (length <= MIN_BLOCK_SIZE) {
        // ��������� �������� ������������ ���������������
        for_each(first, last, f);
    }
    else {
        // ����� �������� �� ��� �����
        Iterator mid = first;
        advance(mid, length / 2);

        // ��������� ����� ����� � ��������� ������
        auto handle = async(launch::async,
            parallel_for_each<Iterator, Func>,
            first, mid, f);

        // ������������ ������ ����� � ������� ������
        parallel_for_each(mid, last, f);

        // ��� ����� ������
        handle.get();
    }
}

int main() {
    vector<int> data(1000000);
    iota(data.begin(), data.end(), 1);

    parallel_for_each(data.begin(), data.end(), [](int& x) { x += 1; });

    // ��������
    cout << "First 10 elements after parallel_for_each: ";
    for (int i = 0; i < 10; i++) cout << data[i] << " ";
    cout << endl;
}
