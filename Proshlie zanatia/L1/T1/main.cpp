#include <iostream>
#include <limits>

enum class MONTHS
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

int main()
{
    int num;
    do {

        std::cout << "Enter month number: ";
        std::cin >> num;

        if (num != 0) {
            switch (static_cast<MONTHS>(num))
            {
            case MONTHS::January: std::cout << "January" << std::endl; break;
            case MONTHS::February: std::cout << "February" << std::endl; break;
            case MONTHS::March: std::cout << "March" << std::endl; break;
            case MONTHS::April: std::cout << "April" << std::endl; break;
            case MONTHS::May: std::cout << "May" << std::endl; break;
            case MONTHS::June: std::cout << "June" << std::endl; break;
            case MONTHS::July: std::cout << "July" << std::endl; break;
            case MONTHS::August: std::cout << "August" << std::endl; break;
            case MONTHS::September: std::cout << "September" << std::endl; break;
            case MONTHS::October: std::cout << "October" << std::endl; break;
            case MONTHS::November: std::cout << "November" << std::endl; break;
            case MONTHS::December: std::cout << "December" << std::endl; break;
            default:
                std::cout << "Wrong month number" << std::endl;
                break;
            }
            std::cout <<std::endl;
        }
        else {
            std::cout << "Goodbye!" << std::endl;
        }
        std::cin.clear();
    } while (num != 0);
}