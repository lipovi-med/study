#include <iostream>
#include <string>
using namespace std;

class Figure {
protected:
	string name;

public:
	virtual void print_info() const {};
	string getName() { return name; };
};

class Triangle : public Figure {
protected:
	unsigned a, b, c, A, B, C;

public:
	Triangle(unsigned a, unsigned b, unsigned c, unsigned A, unsigned B, unsigned C) :
		a(a), b(b), c(c), A(A), B(B), C(C) {
		name = "Triangle";
	}
	void print_info() const override {
		cout << name << ":" << endl;
		cout << "  Sides: a=" << get_a() << ", b=" << get_b() << ", c=" << get_c() << endl;
		cout << "  Angles: A=" << get_A() << ", B=" << get_B() << ", C=" << get_C() << endl;
		cout << endl;
	}

	unsigned get_a() const { return a; }
	unsigned get_b() const { return b; }
	unsigned get_c() const { return c; }
	unsigned get_A() const { return A; }
	unsigned get_B() const { return B; }
	unsigned get_C() const { return C; }
};

class RectengularTriangle : public Triangle {
public:
	RectengularTriangle(unsigned a, unsigned b, unsigned c, unsigned A, unsigned B) :
		Triangle(a, b, c, A, B, 90) {
		name = "RectengularTriangle";
	}

};

class IsoscelesTriangle : public Triangle {
public:
	IsoscelesTriangle(unsigned a, unsigned b, unsigned A, unsigned B) :
		Triangle(a, b, a, A, B, A) {
		name = "IsoscelesTriangle";
	}
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(unsigned a) :
		IsoscelesTriangle(a, a, 60, 60) {
		name = "EquilateralTriangle";
	}
};

class Quadrangle : public Figure {
protected:
	unsigned a, b, c, d, A, B, C, D;

public:
	Quadrangle(unsigned a, unsigned b, unsigned c, unsigned d, unsigned A, unsigned B, unsigned C, unsigned D) :
		a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
		name = "Quadrangle";
	}
	void print_info() const override {
		cout << name << ":" << endl;
cout << "  Sides: a=" << get_a() << ", b=" << get_b() << ", c=" << get_c() << ", d=" << get_d() << endl;
cout << "  Angles: A=" << get_A() << ", B=" << get_B() << ", C=" << get_C() << ", D=" << get_D() << endl;
cout << endl;
	}

	unsigned get_a() const { return a; }
	unsigned get_b() const { return b; }
	unsigned get_c() const { return c; }
	unsigned get_d() const { return d; }
	unsigned get_A() const { return A; }
	unsigned get_B() const { return B; }
	unsigned get_C() const { return C; }
	unsigned get_D() const { return D; }
};

class Parallelogram : public Quadrangle {
public:
	Parallelogram(unsigned a, unsigned b, unsigned A, unsigned B) :
		Quadrangle(a, b, a, b, A, B, A, B) {
		name = "Parallelogram";
	}
};

class Rectangle : public Parallelogram {
public:
	Rectangle(unsigned a, unsigned b) :
		Parallelogram(a, b, 90, 90) {
		name = "Rectangle";
	}
};

class Rhomb : public Parallelogram {
public:
	Rhomb(unsigned a, unsigned A, unsigned B) :
		Parallelogram(a, a, A, B) {
		name = "Rhomb";
	}
};

class Square : public Rhomb {
public:
	Square(unsigned a) :
		Rhomb(a, 90, 90) {
		name = "Square";
	}
};

void print_info(const Figure* figure) {
	figure->print_info();
}


int main()
{
	Figure F;
	Triangle T(10,20,30,50,60,70);
	RectengularTriangle RT(10,20,30,50,60);
	IsoscelesTriangle IT(10,20,50,60);
	EquilateralTriangle ET(10);
	Quadrangle Q(10,20,30,40,50,60,70,80);
	Parallelogram P(10,20,50,60);
	Rectangle R(10,20);
	Rhomb Rb(10,50,60);
	Square S(10);

	print_info(&T);
	print_info(&RT);
	print_info(&IT);
	print_info(&ET);
	print_info(&Q);
	print_info(&P);
	print_info(&R);
	print_info(&Rb);
	print_info(&S);


}