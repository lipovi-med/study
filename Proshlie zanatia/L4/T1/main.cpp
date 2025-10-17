#include <iostream>
#include <string>
using namespace std;

class Figure {
protected:
	string name;
	unsigned number_of_sides;
	Figure(string name, unsigned number_of_sides) {
		this->name = name;
		this->number_of_sides = number_of_sides;
	}
public:
	Figure() : Figure("Figure", 0) {};
	unsigned getNumberOfSides() { return number_of_sides; }
	string getName() { return name; }
};

class Triangle : public Figure {
public:
	Triangle() : Figure("Triangle", 3) {}
};

class Quadrangle : public Figure {
public:
	Quadrangle() : Figure("Quadrangle", 4) {}
};
int main()
{
	Figure f;
	Triangle t;
	Quadrangle q;
	cout << "Number of sides:" << endl;
	cout << f.getName() << ": " << f.getNumberOfSides() << endl;
	cout << t.getName() << ": " << t.getNumberOfSides() << endl;
	cout << q.getName() << ": " << q.getNumberOfSides() << endl;

}