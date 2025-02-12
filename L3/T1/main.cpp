#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class ADDRES_LIST
{
	ADDRES_LIST(string city, string street, string house_number, string room_number) : city{city}, street{street}, house_number{house_number}, room_number{room_number} {}
	string city;
	string street;
	string house_number;
	string room_number;
};

int main()
{
	ifstream inputF("input.txt");
	if (inputF.is_open()) {







	}
	else {
		cout << "ERROE! The file wasn't opened!"
	}
}