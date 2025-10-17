#include <iostream>
#include <string>
using namespace std;

struct BANK_ACCOUNT
{
	string name;
	unsigned long number;
	long double balance;
};

void show_BANK_ACCOUNT(BANK_ACCOUNT account)
{
	cout << "Yours bank account:\n";
	cout << "\t\t" << account.name << endl;
	cout << "\t\t" << account.number << endl;
	cout << "\t\t" << account.balance << endl;
}

void change_balance(BANK_ACCOUNT& account,long double new_balance)
{
	account.balance = new_balance;
}

int main()
{
	long double money;
	BANK_ACCOUNT account_1;
	cout << "Enter the account number: ";
	cin >> account_1.number;
	cin.clear();
	cout << "Enter owners Name: ";
	cin >> account_1.name;
	cin.clear();
	cout << "Enter account balance: ";
	cin >> account_1.balance;
	cin.clear();
	cout << "Enter new balance: ";
	cin >> money;
	change_balance(account_1, money);
	show_BANK_ACCOUNT(account_1);
}