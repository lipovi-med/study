#include <iostream>
#include <vector>
using namespace std;

template<typename t>

class table {
	int row;
	int col;
	vector<vector<t>> cell;
public:
	table(int R, int C) : row(R), col(C), cell(R, vector<t>(C)) {};

	vector<t>& operator[](int index) {
		return cell[index];
	}
	const vector<t>& operator[](int index) const {
		return cell[index];
	}

	void Size() const {
		cout << "Size: " << row << " x " << col << endl;
	}
};




int main() {
	auto test = table<int>(2, 3);
	test[0][0] = 4;
	std::cout << test[0][0]; // выводит 4
}