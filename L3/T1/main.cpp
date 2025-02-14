#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class ADDRES_LIST
{
	string city;
	string street;
	string house_number;
	string room_number;
public:
	void set_city(string city) { this->city = city; }
	void set_street(string street) { this->street = street; }
	void set_house_number(string house_number) { this->house_number = house_number; }
	void set_room_number(string room_number) { this->room_number = room_number; }

	string get_city() const{ return city; }
	string get_street() const { return street; }
	string get_house_number() const { return house_number; }
	string get_room_number() const { return room_number; }
};

int main()
{
	ifstream inputF("in.txt");
	if (inputF.is_open()) {
		int NumberOfAddreses;
		inputF >> NumberOfAddreses;
		ADDRES_LIST* point = new ADDRES_LIST[NumberOfAddreses];
		for (int i = 0; i < NumberOfAddreses; i++) {
			string buff;
			inputF >> buff;
			point[i].set_city(buff);
			inputF >> buff;
			point[i].set_street(buff);
			inputF >> buff;
			point[i].set_house_number(buff);
			inputF >> buff;
			point[i].set_room_number(buff);
		}
		inputF.close();

		ofstream outputF("out.txt");
		outputF << NumberOfAddreses << endl;
		for (int i = NumberOfAddreses; i > 0; i--) {
			outputF << point[i - 1].get_city() << ", ";
			outputF << point[i - 1].get_street() << ", ";
			outputF << point[i - 1].get_house_number() << ", ";
			outputF << point[i - 1].get_room_number() << endl;
		}

		outputF.close();
		delete[] point;

		cout << "The recording format has been changed.";
	}
	else {
		cout << "ERROE! The file wasn't opened!";
	}
}