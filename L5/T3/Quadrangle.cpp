#include <iostream>

#include "Figure.h"
#include "Quadrangle.h"

using namespace std;

Quadrangle::Quadrangle(unsigned a, unsigned b, unsigned c, unsigned d, unsigned A, unsigned B, unsigned C, unsigned D) :
	a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
	name = "Quadrangle";
}; 
void Quadrangle::print_info() const {
	cout << name << ":" << endl;
	cout << "  Sides: a=" << get_a() << ", b=" << get_b() << ", c=" << get_c() << ", d=" << get_d() << endl;
	cout << "  Angles: A=" << get_A() << ", B=" << get_B() << ", C=" << get_C() << ", D=" << get_D() << endl;
	cout << endl;
};

	unsigned Quadrangle::get_a() const { return a; };
	unsigned Quadrangle::get_b() const { return b; };
	unsigned Quadrangle::get_c() const { return c; };
	unsigned Quadrangle::get_d() const { return d; };
	unsigned Quadrangle::get_A() const { return A; };
	unsigned Quadrangle::get_B() const { return B; };
	unsigned Quadrangle::get_C() const { return C; };
	unsigned Quadrangle::get_D() const { return D; };