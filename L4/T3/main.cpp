#include <iostream>
#include <string>
using namespace std;

class Figure {
protected:
	string name;
	unsigned number_of_sides;
	bool right_or_not;

public:
	Figure() : name("Figure"), number_of_sides(0), right_or_not(true) {}
	virtual void print_info() {
		cout << getName() << ':' << endl;
		getRightOrNot();
		cout << "Number of sides:" << getNumberOfSides() << endl;
	};
	virtual bool rightOrNot() = 0;
	string getName() { return name; };
	unsigned getNumberOfSides() { return number_of_sides; }
	void getRightOrNot() {
		if (right_or_not) {
			cout << "Right figure" << endl;
		}
		else {
			cout << "Wrong figure" << endl;
		}
	}
	virtual ~Figure() {};
};

class Triangle : public Figure {
protected:
	float a, b, c, A, B, C;

public:
	Triangle(float a, float b, float c, float A, float B, float C) :
		a(a), b(b), c(c), A(A), B(B), C(C) {
		name = "Triangle";
		number_of_sides = 3;
	}
	bool rightOrNot() override {
		right_or_not = (A + B + C == 180);
		return right_or_not;
	}
	void print_info() override {
		rightOrNot();
		Figure::print_info();
		cout << "  Sides: a=" << get_a() << ", b=" << get_b() << ", c=" << get_c() << endl;
		cout << "  Angles: A=" << get_A() << ", B=" << get_B() << ", C=" << get_C() << endl;
		cout << endl;
	}

	float get_a() const { return a; }
	float get_b() const { return b; }
	float get_c() const { return c; }
	float get_A() const { return A; }
	float get_B() const { return B; }
	float get_C() const { return C; }
};

class RectengularTriangle : public Triangle {
public:
	RectengularTriangle(float a, float b, float c, float A, float B) :
		Triangle(a, b, c, A, B, 90) {
		name = "RectengularTriangle";
	}

};

class IsoscelesTriangle : public Triangle {
public:
	IsoscelesTriangle(float a, float b, float A, float B) :
		Triangle(a, b, a, A, B, A) {
		name = "IsoscelesTriangle";
	}
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(float a) :
		IsoscelesTriangle(a, a, 60, 60) {
		name = "EquilateralTriangle";
	}
};

class Quadrangle : public Figure {
protected:
	float a, b, c, d, A, B, C, D;

public:
	Quadrangle(float a, float b, float c, float d, float A, float B, float C, float D) :
		a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
		name = "Quadrangle";
		number_of_sides = 4;
	}
	bool rightOrNot() override {
		right_or_not = (A + B + C +D == 360);
		return right_or_not;
	}
	void print_info() override {
		rightOrNot();
		Figure::print_info();
		cout << "  Sides: a=" << get_a() << ", b=" << get_b() << ", c=" << get_c() << ", d=" << get_d() << endl;
		cout << "  Angles: A=" << get_A() << ", B=" << get_B() << ", C=" << get_C() << ", D=" << get_D() << endl;
		cout << endl;
	}

	float get_a() const { return a; }
	float get_b() const { return b; }
	float get_c() const { return c; }
	float get_d() const { return d; }
	float get_A() const { return A; }
	float get_B() const { return B; }
	float get_C() const { return C; }
	float get_D() const { return D; }
};

class Parallelogram : public Quadrangle {
public:
	Parallelogram(float a, float b, float A, float B) :
		Quadrangle(a, b, a, b, A, B, A, B) {
		name = "Parallelogram";
	}
};

class Rectangle : public Parallelogram {
public:
	Rectangle(float a, float b) :
		Parallelogram(a, b, 90, 90) {
		name = "Rectangle";
	}
};

class Rhomb : public Parallelogram {
public:
	Rhomb(float a, float A, float B) :
		Parallelogram(a, a, A, B) {
		name = "Rhomb";
	}
};

class Square : public Rhomb {
public:
	Square(float a) :
		Rhomb(a, 90, 90) {
		name = "Square";
	}
};

void print_info(Figure* figure) {
	figure->print_info();
}


int main()
{
	
	Triangle T(10, 20, 30, 50, 60, 70);
	RectengularTriangle RT1(10, 20, 30, 50, 60);
	RectengularTriangle RT2(10, 20, 30, 50, 40);
	IsoscelesTriangle IT(10, 20, 50, 60);
	EquilateralTriangle ET(10);
	Quadrangle Q(10, 20, 30, 40, 50, 60, 70, 80);
	Parallelogram P(10, 20, 50, 60);
	Rectangle R(10, 20);
	Rhomb Rb(10, 50, 60);
	Square S(10);

	
	print_info(&T);
	print_info(&RT1);
	print_info(&RT2);
	print_info(&IT);
	print_info(&ET);
	print_info(&Q);
	print_info(&P);
	print_info(&R);
	print_info(&Rb);
	print_info(&S);


}