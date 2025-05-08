#include <iostream>
using namespace std;

class Fraction
{
private:
    int numerator_;
    int denominator_;

    int NOD(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void reduce() {
        int divisor = NOD(abs(numerator_), abs(denominator_));
        numerator_ /= divisor;
        denominator_ /= divisor;
        if (denominator_ < 0) {
            denominator_ = -denominator_;
            numerator_ = -numerator_;
        }
    }
public:
    Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        numerator_ = numerator;
        denominator_ = denominator;
        reduce();
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator_ * other.denominator_ + other.numerator_ * denominator_, denominator_ * other.denominator_);
    }
    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator_ * other.denominator_ - other.numerator_ * denominator_, denominator_ * other.denominator_);
    }
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
    }
    Fraction operator/(const Fraction& other) const {
        if (other.numerator_ == 0) {
            throw invalid_argument("Division by zero fraction.");
        }
        return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
    }

    Fraction& operator++() {
        numerator_ += denominator_;
        reduce();
        return *this;
    }
    Fraction operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }
    Fraction& operator--() {
        numerator_ -= denominator_;
        reduce();
        return *this;
    }
    Fraction operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    void Print() const {
        cout << numerator_ << '/' << denominator_;
    }

    void PRINT(const Fraction& one, const Fraction& two, char sign) {
        one.Print();
        cout << ' ' << sign << ' ';
        two.Print();
        cout << " = ";
        this->Print();
        cout << endl;
    }

    void PrintValue(int fractionNumber) const {
        cout << "Значение дроби " << fractionNumber << " = ";
        this->Print();
        cout << endl;
    }
};

int main()
{
    Fraction* ptrArr[2]{ nullptr, nullptr };
    for (int i = 0; i < 2; i++) {
        int num, den;
        cout << "Enter numerator of fraction " << i + 1 << ": ";
        cin >> num;
        cout << "Enter denominator of fraction " << i + 1 << ": ";
        cin >> den;
        try {
            ptrArr[i] = new Fraction(num, den);
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            --i;
        }
    }

    Fraction SUM = *ptrArr[0] + *ptrArr[1];
    SUM.PRINT(*ptrArr[0], *ptrArr[1], '+');
    Fraction SUB = *ptrArr[0] - *ptrArr[1];
    SUB.PRINT(*ptrArr[0], *ptrArr[1], '-');
    Fraction MUL = *ptrArr[0] * *ptrArr[1];
    MUL.PRINT(*ptrArr[0], *ptrArr[1], '*');
    Fraction DIV = *ptrArr[0] / *ptrArr[1];
    DIV.PRINT(*ptrArr[0], *ptrArr[1], '/');


    Fraction beforeIncrement = *ptrArr[0];
    Fraction MUL_PREF_INCR = ++(*ptrArr[0]) * *ptrArr[1];
    cout << "++";
    beforeIncrement.Print();
    cout << " * ";
    ptrArr[1]->Print();
    cout << " = ";
    MUL_PREF_INCR.Print();
    cout << endl;
    cout << "Value of the fraction 1 = ";
    ptrArr[0]->Print();
    cout << endl;

    Fraction beforeDecrement = *ptrArr[0];
    Fraction MUL_POST_DECR = (*ptrArr[0])-- * *ptrArr[1];
    beforeDecrement.Print();
    cout << "-- * ";
    ptrArr[1]->Print();
    cout << " = ";
    MUL_POST_DECR.Print();
    cout << endl;
    cout << "Value of the fraction 1 = ";
    ptrArr[0]->Print();
    cout << endl;

    delete ptrArr[0];
    delete ptrArr[1];

    return 0;
}
