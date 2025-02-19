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
	ADDRES_LIST() {};
	ADDRES_LIST(string city, string street, string house_number, string room_number)
		: city(city), street(street), house_number(house_number), room_number(room_number) {};

	string get_city() const { return city; }
	string get_street() const { return street; }
	string get_house_number() const { return house_number; }
	string get_room_number() const { return room_number; }
};

void plase_switch(ADDRES_LIST& pointBIG, ADDRES_LIST& pointSMALL)
{
	ADDRES_LIST buff;
	buff = pointBIG;
	pointBIG = pointSMALL;
	pointSMALL = buff;
}

void Sorter(ADDRES_LIST* point,const int NumberOfAddreses)
{
	bool changes;
	do {
		changes = false;
		for (int i = 0; i < NumberOfAddreses - 1; i++) {
			if (point[i].get_city() > point[i + 1].get_city()) {
				plase_switch(point[i], point[i + 1]);
				changes = true;
			}
		}
	} while (changes == true);
};

int main()
{
	ifstream inputF("in.txt");
	if (inputF.is_open()) {
		int NumberOfAddreses;
		inputF >> NumberOfAddreses;
		ADDRES_LIST* point = new ADDRES_LIST[NumberOfAddreses];
		for (int i = 0; i < NumberOfAddreses; i++) {
			string city, street, house_number, room_number;
			inputF >> city;
			inputF >> street;
			inputF >> house_number;
			inputF >> room_number;
			point[i] = ADDRES_LIST(city, street, house_number, room_number);
		}
		inputF.close();

		Sorter(point, NumberOfAddreses);

		ofstream outputF("out.txt");
		outputF << NumberOfAddreses << endl;
		for (int i = 0; i < NumberOfAddreses; i++) {
			outputF << point[i].get_city() << ", ";
			outputF << point[i].get_street() << ", ";
			outputF << point[i].get_house_number() << ", ";
			outputF << point[i].get_room_number() << endl;
		}

		outputF.close();
		delete[] point;

		cout << "The recording format has been changed.";
	}
	else {
		cout << "ERROE! The file wasn't opened!";
	}
}