#include <iostream>
using namespace std;

class Counter
{
    private:
        int cntr;
    public:
        void increase() {
            cntr++;
        }
        void reduce() {
            cntr--;
        }
        void show_result() const {
            cout << cntr << endl;
        }
        void SetInitialValue(int input) {
            cntr = input;
        }


};

int main()
{
    char char_input;
    int int_input;
    bool crct = false;
    Counter counter;

    cout << "Do you whant to set the initial value? Y/N: ";
    do {
        cin >> char_input;
        if(char_input == 'Y' || char_input == 'y') {
            cout << "Enter initial value: ";
            cin >> int_input;
            counter.SetInitialValue(int_input);
            crct = true;
        } else {
            if(char_input == 'N' || char_input == 'n'){
                counter.SetInitialValue(0);
                crct = true;
            } else {
                cout << "Don't undrstend Y/N? : ";
                crct = false;
            }
        }
            
    } while(crct != true);
    do {
        cout << "Enter comand ('+', '-', '=' or 'x'): ";
        cin >> char_input;
        switch (char_input)
        {
        case '+':
            counter.increase();
            break;
        case '-':
            counter.reduce();
            break;
        case '=':
            counter.show_result();
            break;        
        case 'x':
            break;
        
        default:
            cout << "Don't undrstend.\nPlease. ";
            break;
        }
    } while(char_input != 'x');
    cout << "Goodbye!";
   

}