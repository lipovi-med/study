#include <iostream>
#include <string>

class ForbidenLangthException : public std::exception {
public:
	const char* what() const override { return "You have entered a word of a forbidden length! Goodbye!"; }
};

int length_check(std::string str, int forbidden_length) {
	if (str.length() == forbidden_length) throw ForbidenLangthException();
	return str.length();
}

int main() {
	int forbidden_langth;
	std::cout << "Enter forbidden length: ";
	std::cin >> forbidden_langth;
	try {
		while (true) {
			std::string str;
			int str_length;
			std::cout << "Enter a word: ";
			std::cin >> str;
			str_length = length_check(str, forbidden_langth);
			std::cout << "The length of the word \"" << str << "\" is " << str_length << std::endl;
		}
	}
	catch(const ForbidenLangthException& ex) {
		std::cout << ex.what() << std::endl;
	}
}