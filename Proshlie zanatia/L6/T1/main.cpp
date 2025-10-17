#include <iostream>

#define MODE 1
#ifndef MODE
#error "MODE needs to be defined"
#endif

#if MODE == 1
int add(int a, int b) {
    return a + b;
}
#endif

int main() {
    if (MODE == 0) {
        std::cout << "Working in training mode" << std::endl;
    }
    else if (MODE == 1) {
        std::cout << "Working in combat mode" << std::endl;

        int num1, num2;
        std::cout << "Enter number 1: ";
        std::cin >> num1;
        std::cout << "Enter number 2: ";
        std::cin >> num2;

        std::cout << "Result: " << add(num1, num2) << std::endl;
    }
    else {
        std::cout << "Unknown mode. Shutdown." << std::endl;
    }

    return 0;
}