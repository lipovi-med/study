#include <iostream>
#include "math.h"
using namespace std;

enum MathOperatin{
	ADD = 1,
	SUB,
	MUL,
	DIV,
	EXP
};

int main()
{
	int x = 0, y = 0, input = 0;
	cout << "Enter 1st number: ";
	cin >> x;
	cout << "Enter 2nd number: ";
	cin >> y;
	cout << "Enter operation \t1 - addition\n\t\t\t2 - subtraction\n\t\t\t3 - multiplication\n\t\t\t4 - division\n\t\t\t5 - exponentiation\n\t--->";
	cin >> input;
	switch (input)
	{
	case MathOperatin::ADD:
		cout << x << " + " << y << " = " << addition(x, y); break;
	case MathOperatin::SUB:
		cout << x << " - " << y << " = " << subtraction(x, y); break;
	case MathOperatin::MUL:
		cout << x << " * " << y << " = " << multiplication(x, y); break;
	case MathOperatin::DIV:
		cout << x << " / " << y << " = " << division(x, y); break;
	case MathOperatin::EXP:
		cout << x << " ^ " << y << " = " << exponentiation(x, y); break;
	default: 
		break;
	}
}