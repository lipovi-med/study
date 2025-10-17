#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

template <typename T>
void move_vectors(vector<T>& source, vector<T>& dest) {

    //dest.insert(dest.end(),
    //    make_move_iterator(source.begin()),
    //    make_move_iterator(source.end()));

    //source.clear();

    dest = move(source);
}

int main() {
    vector<string> one = { "test_string1", "test_string2" };
    vector<string> two;

    move_vectors(one, two);

    cout << "Source vector size: " << one.size() << endl;
    cout << "Destination vector contains: ";
    for (const auto& s : two)
        cout << s << " ";
    cout << endl;
}
