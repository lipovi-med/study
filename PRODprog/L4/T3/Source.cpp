#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DivisibleByThreeCounter {
private:
    int sum;
    int count;

public:
    DivisibleByThreeCounter() : sum(0), count(0) {}

    void operator()(int number) {  // Функтор
        if (number % 3 == 0) {
            sum += number;
            count++;
        }
    }

    int get_sum() const {
        return sum;
    }

    int get_count() const {
        return count;
    }
};

template<typename T>
ostream& operator<<(ostream& OS, const vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        OS << vec[i];
        if (i != vec.size() - 1) {
            OS << " ";
        }
    }
    return OS;
}

int main() {
    vector<int> numbers = { 4, 1, 3, 6, 25, 54 };
    cout << "[IN]: " << numbers << endl;

    DivisibleByThreeCounter counter = for_each( numbers.begin(), numbers.end(), DivisibleByThreeCounter());

    cout << "[OUT]: get_sum() = " << counter.get_sum() << endl;
    cout << "[OUT]: get_count() = " << counter.get_count() << endl;

    return 0;
}