#include <iostream>
#include <cmath>

const float EPSILON = std::numeric_limits<float>::epsilon();

class Fraction
{
private:
    int numerator_;
    int denominator_;

    float devision() {
        return static_cast<float>(numerator_) / static_cast<float>(denominator_);
    }
    bool equal(float x, float y) {
        return fabs(x - y) < EPSILON;
    }

public:
    Fraction(int numerator, int denominator) {
        numerator_ = numerator;
        denominator_ = denominator;
    }
    bool operator==(Fraction other) {
        return equal(devision(), other.devision());
    }
    bool operator!=(Fraction other) {
        return !(*this == other);
    }
    bool operator>(Fraction other) {
        return devision() > other.devision();
    }
    bool operator<(Fraction other) {
        return other > *this;
    }
    bool operator>=(Fraction other) {
        return !(*this < other);
    }
    bool operator<=(Fraction other) {
        return !(*this > other);
    }

};

int main()
{
    Fraction f1(4, 3);
    Fraction f2(6, 11);

    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';

    return 0;
}