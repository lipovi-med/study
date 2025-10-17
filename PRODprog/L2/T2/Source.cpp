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
		Sarr = new int[size];
	}

	smart_array(const smart_array& other)
		: size(other.size), current_pos(other.current_pos) {
		Sarr = new int[size];
		for (unsigned int i = 0; i < current_pos; i++) {
			Sarr[i] = other.Sarr[i];
		}
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
	int get_element(int pos) const {
		if (pos >= 0 && pos < current_pos) {
			return Sarr[pos];
		}
		else {
			throw out_of_range("В массиве нет такой ячейки.");
		}
	};

	smart_array& operator=(const smart_array& other) {
		if (this == &other) return *this;
		delete[] this->Sarr;
		this->size = other.size;
		this->current_pos = other.current_pos;
		Sarr = new int[size];
		for (unsigned i = 0; i < current_pos; i++) {
			Sarr[i] = other.Sarr[i];
		}
		return *this;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);

		smart_array new_array(2);
		new_array.add_element(44);
		new_array.add_element(34);

		arr = new_array;
	}
	catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
	return 0;
}