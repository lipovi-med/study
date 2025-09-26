#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <utility>   // ��� std::swap
#include <random>
using namespace std;

// ����������� ����� �������� � ����������
void find_min_async(const vector<int>& arr, int start, promise<int> prom) {
    int minIndex = start;
    for (int i = start + 1; i < arr.size(); i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    prom.set_value(minIndex); // ���������� ������ ��������
}

// ���������� ������� � �������������� promise/future
void selection_sort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        promise<int> prom;
        future<int> fut = prom.get_future();

        // ��������� ����������� ����� ��������
        thread t(find_min_async, cref(arr), i, move(prom));

        // ��� ���������
        int minIndex = fut.get();
        t.join();

        // ������ ������� ������� � ����������� ��������
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

int main() {
    vector<int> arr(20);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    for (auto& x : arr) { x = dis(gen); }


    cout << "Before sort: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    selection_sort(arr);

    cout << "After sort:  ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
