#include <iostream>

using namespace std;

class smart_array {
private:
	unsigned int size;
	int* Sarr;
	unsigned int current_pos = 0;
public:
	smart_array(unsigned int size) {
		this->size = size;
		Sarr = new int [size]();
	}
	~smart_array() { delete[] Sarr; }

	void add_element(int x) {
		if (current_pos < size) {
			Sarr[current_pos] = x;
			current_pos++;
		}
		else {
			throw out_of_range("Массив переполнен!");
		}
	};
	int get_element(int pos) {
		if (pos >= 0 && pos < size) {
			return Sarr[pos];
		}
		else {
			throw out_of_range("В массиве нет такой ячейки.");
		}
	};
};

int main() {
	setlocale(LC_ALL, "Russian");
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		cout << arr.get_element(1) << endl;
	}
	catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
}