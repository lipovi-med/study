#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>

using namespace std;

template <typename Container>
void print_container(const Container& c) {
    if (c.empty()) {
        cout << "(empty)" << endl;
        return;
    }

    bool first = true;
    for (const auto& elem : c) {
        if (!first)
            cout << ", ";
        cout << elem;
        first = false;
    }
    cout << endl;
}

int main() {
    set<string> test_set = { "one", "two", "three", "four" };
    list<string> test_list = { "one", "two", "three", "four" };
    vector<string> test_vector = { "one", "two", "three", "four" };

    cout << "set: ";
    print_container(test_set);

    cout << "list: ";
    print_container(test_list);

    cout << "vector: ";
    print_container(test_vector);
}
