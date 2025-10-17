#include <iostream>

#include "Figure.h"
#include "Triangle.h"

using namespace std;


	Triangle::Triangle(unsigned a, unsigned b, unsigned c, unsigned A, unsigned B, unsigned C) :
		a(a), b(b), c(c), A(A), B(B), C(C) {
		name = "Triangle";
	}

	void Triangle::print_info() const {
		cout << name << ":" << endl;
		cout << "  Sides: a=" << get_a() << ", b=" << get_b() << ", c=" << get_c() << endl;
		cout << "  Angles: A=" << get_A() << ", B=" << get_B() << ", C=" << get_C() << endl;
		cout << endl;
	}

	unsigned Triangle::get_a() const { return a; }
	unsigned Triangle::get_b() const { return b; }
	unsigned Triangle::get_c() const { return c; }
	unsigned Triangle::get_A() const { return A; }
	unsigned Triangle::get_B() const { return B; }
	unsigned Triangle::get_C() const { return C; }