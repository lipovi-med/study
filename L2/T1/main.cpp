#include <iostream>
using namespace std;

class Calculator
{
private:
double num1, num2;
public:
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
    return (num1 + num2);
};
double multiply() const {
    return (num1 * num2);
};
double subtract_1_2() const {
    return (num1 - num2);
};
double subtract_2_1() const {
    return (num2 - num1);
};
double divide_1_2() const {
    return (num1 / num2);
};
double divide_2_1() const {
    return (num2 / num1);
};
};

int main()
{
    double num1, num2;
    Calculator CALC;

    while(true)
    {
        do {
            cout << "Enter num1: ";
            cin >> num1;
        } while (!CALC.set_num1(num1));

        do {
            cout << "Enter num2: ";
            cin >> num2;
        } while (!CALC.set_num2(num2));
        
        
        cout << "num1 + num2 = " << CALC.add() << endl;
        cout << "num1 - num2 = " << CALC.subtract_1_2() << endl;
        cout << "num2 - num1 = " << CALC.subtract_2_1() << endl;
        cout << "num1 x num2 = " << CALC.multiply() << endl;
        cout << "num1 / num2 = " << CALC.divide_1_2() << endl;
        cout << "num2 / num1 = " << CALC.divide_2_1() << endl;
                
    }
}