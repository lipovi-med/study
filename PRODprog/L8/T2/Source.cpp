#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class big_integer {
private:
    string digits;

public:
    big_integer(const string& value) {
        digits = value;
        reverse(digits.begin(), digits.end());
    }

    big_integer(big_integer&& other) noexcept {
        digits = std::move(other.digits);
    }

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        string result;
        int ostatok = 0;
        long long n = max(digits.size(), other.digits.size());

        for (long long i = 0; i < n; ++i) {
            int d1 = (i < digits.size()) ? digits[i] - '0' : 0;
            int d2 = (i < other.digits.size()) ? other.digits[i] - '0' : 0;
            int sum = d1 + d2 + ostatok;
            result.push_back((sum % 10) + '0');
            ostatok = sum / 10;
        }

        if (ostatok) result.push_back(ostatok + '0');

        reverse(result.begin(), result.end());
        return big_integer(result);
    }

    big_integer operator*(int num) const {
        if (num == 0) return big_integer("0");

        string result;
        int ostatok = 0;
        for (char c : digits) {
            int prod = (c - '0') * num + ostatok;
            result.push_back((prod % 10) + '0');
            ostatok = prod / 10;
        }

        while (ostatok) {
            result.push_back((ostatok % 10) + '0');
            ostatok /= 10;
        }

        reverse(result.begin(), result.end());
        return big_integer(result);
    }

    friend ostream& operator<<(ostream& os, const big_integer& num) {
        string s = num.digits;
        reverse(s.begin(), s.end());
        os << s;
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
}
