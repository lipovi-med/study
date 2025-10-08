#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <random>
#include <condition_variable>
using namespace std;

mutex print_mtx;                // ��� ������ � �������
mutex sync_mtx;                 // ��� ������������� ������
condition_variable cv;          // �������� ���������� ��� ������
int ready_threads = 0;          // ������� ������� ������ � ������
bool start_flag = false;        // ������ � ������

void worker(int index, int workLength, int row, int totalThreads) {
    auto start = chrono::steady_clock::now();
    string progress(workLength, ' ');

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 15);

    // ������� ������ � ������� ������ � ������ �����
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "\033[" << (row + 2) << ";0H"; // +2 ��� ������� �� ���������
        cout << "Thread " << setw(2) << index
            << " (id=" << this_thread::get_id() << ")\t"
            << "[" << progress << "]" << flush;
    }

    // ������, ��� ����� �����
    {
        unique_lock<mutex> lock(sync_mtx);
        ready_threads++;
        if (ready_threads == totalThreads) {
            start_flag = true;
            cv.notify_all(); // ��������� ����� ��������!
        }
        else {
            cv.wait(lock, [] { return start_flag; });
        }
    }

    // ������ ��� ������ �������� ������������ ��������� ��������-����
    for (int i = 0; i < workLength; i++) {
        progress[i] = '#';

        {
            lock_guard<mutex> lock(print_mtx);
            cout << "\033[" << (row + 2) << ";0H";
            cout << "Thread " << setw(2) << index
                << " (id=" << this_thread::get_id() << ")\t"
                << "[" << progress << "]" << flush;
        }

        this_thread::sleep_for(chrono::milliseconds(100 + dis(gen) * 50));
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    {
        lock_guard<mutex> lock(print_mtx);
        cout << "\033[" << (row + 2) << ";0H";
        cout << "Thread " << setw(2) << index
            << " (id=" << this_thread::get_id() << ")\t"
            << "[" << string(workLength, '#') << "] "
            << " completed by " << fixed << setprecision(2)
            << elapsed.count() << " ms   " << flush;
    }
}

int main() {
    int numThreads = 5;   // ���������� �������
    int workLength = 20;  // ����� ��������-����

    cout << "\033[2J\033[H";   // ������� ������
    cout << "\033[?25l";       // ������ ������

    vector<thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(worker, i + 1, workLength, i, numThreads);
    }

    for (auto& t : threads) t.join();

    cout << "\033[?25h"; // ������� ������
    cout << "\033[" << numThreads + 4 << ";0H";
    cout << "\nAll threads are completed!\n";
    return 0;
}
