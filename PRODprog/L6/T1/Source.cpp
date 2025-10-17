#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void make_unique(vector<int>& v) {

    sort(v.begin(), v.end());

    auto last = unique(v.begin(), v.end());

    v.erase(last, v.end());
}

int main() {

    vector<int> v = { 1, 1, 2, 5, 6, 1, 2, 4 };

    make_unique(v);

    for (int n : v)
        cout << n << " ";

    return 0;
}
