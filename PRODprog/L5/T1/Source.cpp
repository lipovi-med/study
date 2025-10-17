#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    string text;
    cout << "[IN]: ";
    getline(cin, text);

    unordered_map<char, int> freq;

    for (char c : text) {
        freq[c]++;
    }

    vector<pair<char, int>> vec(freq.begin(), freq.end());

    sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    cout << "[OUT]:\n";
    for (auto& [ch, count] : vec) {
        cout << ch << ": " << count << "\n";
    }

    return 0;
}
