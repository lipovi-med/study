#include <iostream>
#include <set>

using namespace std;

int main() {
    cout << "[IN]:" << endl;
    int n;
    cin >> n;

    set<int, greater<int>> numbers;

    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        numbers.insert(value);
    }

    cout << "[OUT]:" << endl;

    for (int num : numbers) {
        cout << num << endl;
    }

    return 0;
}
