#include <iostream>
#include <string>
using namespace std;

struct ADDRESS_INF
{
	string city_name;
	string street;
	string house_number;
	string room_number;
	unsigned int index;
};

void _print_address(ADDRESS_INF adrs)
{
	cout << "City: " << adrs.city_name << endl;
	cout << "Street: " << adrs.street << endl;
	cout << "House number: " << adrs.house_number << endl;
	cout << "Room number: " << adrs.room_number << endl;
	cout << "Index: " << adrs.index << endl;
	cout << endl;
}

int main()
{
	ADDRESS_INF* _address = new ADDRESS_INF[3];

	_address[0].city_name = "Kazan";
	_address[0].street = "Karl Marks";
	_address[0].house_number = "58/12";
	_address[0].room_number = "3a";
	_address[0].index = 420015;

	_address[1].city_name = "Nijni Novgorod";
	_address[1].street = "Poltavskaia";
	_address[1].house_number = "3k1";
	_address[1].room_number = "98";
	_address[1].index = 603024;

	_address[2].city_name = "Yoshkar-Ola";
	_address[2].street = "Komsomolskaia";
	_address[2].house_number = "145";
	_address[2].room_number = "20";
	_address[2].index = 424000;

	for (int i = 0; i < 3; i++) {
		_print_address(_address[i]);
	}

	delete[] _address;
}