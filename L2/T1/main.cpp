#include <iostream>
using namespace std;

class Calculator
{
public:
double num1, num2;
bool set_num1(double num1) {
    if(num1 != 0) {
        this->num1 = num1;
        return true;
    }
    else {
        cout << "Value must be !=0. Truy again." << endl;
        return false;
    }
};
bool set_num2(double num2) {
    if(num2 != 0) {
        this->num2 = num2;
        return true;
    }
    else {
        cout << "Value must be !=0. Truy again." << endl;
        return false;
    }
};
double add() const {
    cout << "num1 + num2 = ";
    return (num1 + num2);
};
double multiply() const {
    cout << "num1 x num2 = ";
    return (num1 * num2);
};
double subtract_1_2() const {
    cout << "num1 - num2 = ";
    return (num1 - num2);
};
double subtract_2_1() const {
    cout << "num2 - num1 = ";
    return (num2 - num1);
};
double divide_1_2() const {
    cout << "num1 / num2 = ";
    return (num1 / num2);
};
double divide_2_1() const {
    cout << "num2 / num1 = ";
    return (num2 / num1);
};
};

int main()
{
    double num1, num2;
    Calculator CALC;

    while(int i = 0 != 1)
    {
        do {
            cout << "Enter num1: ";
            cin >> num1;
        } while (!CALC.set_num1(num1));

        do {
            cout << "Enter num2: ";
            cin >> num2;
        } while (!CALC.set_num2(num2));
        
        
        cout << CALC.add() << endl;
        cout << CALC.subtract_1_2() << endl;
        cout << CALC.subtract_2_1() << endl;
        cout << CALC.multiply() << endl;
        cout << CALC.divide_1_2() << endl;
        cout << CALC.divide_2_1() << endl;
                
    }
}