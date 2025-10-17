#include <iostream>
#include <vector>
using namespace std;

template<typename T>
T pwr(T number) {
	return number * number;
}

template<typename T>
vector<T> pwr(const vector<T>& V) {
	vector<T> rslt;
	for (const auto x : V) {
		rslt.push_back(x * x);
	}
	return rslt;
}

template<typename T>
ostream& operator<<(ostream& OS, const vector<T>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		OS << vec[i];
		if (i != vec.size() - 1) {
			OS << ", ";
		}
	}
	return OS;
}



int main(){
	cout << "[IN]: 4"<<endl;
	cout << "[OUT]: " << pwr(4) << endl;

	cout << "[IN]: 3, 4, 5"<< endl;
	vector<int> vec{ 3, 4, 5 };
	cout << "[OUT]: " << pwr(vec) << endl;
}