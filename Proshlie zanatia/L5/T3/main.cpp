#include <iostream>
#include <string>

#include "Figure.h"
#include "Triangle.h"
#include "RectengularTriangle.h"
#include "IsoscelesTriangle.h"
#include "EquilateralTriangle.h"
#include "Quadrangle.h"
#include "Rectangle.h"
#include "Parallelogram.h"
#include "Rhomb.h"
#include "Square.h"
using namespace std;

void print_info(const Figure* figure) {
	figure->print_info();
}


int main()
{
	Figure F;
	Triangle T(10, 20, 30, 50, 60, 70);
	RectengularTriangle RT(10, 20, 30, 50, 60);
	IsoscelesTriangle IT(10, 20, 50, 60);
	EquilateralTriangle ET(10);
	Quadrangle Q(10, 20, 30, 40, 50, 60, 70, 80);
	Parallelogram P(10, 20, 50, 60);
	Rectangle R(10, 20);
	Rhomb Rb(10, 50, 60);
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