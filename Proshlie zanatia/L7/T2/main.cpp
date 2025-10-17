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
#include "FigureCreationException.h"
using namespace std;

void print_info(const Figure* figure) {
	figure->print_info();
}


int main()
{
	setlocale(LC_ALL, "Russian");

	Figure F;
	try {
		Triangle T(10, 20, 30, 50, 60, 70);
		print_info(&T);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		RectengularTriangle RT(10, 20, 30, 30, 60);
		print_info(&RT);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		IsoscelesTriangle IT(10, 20, 50, 60);
		print_info(&IT);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		EquilateralTriangle ET(10);
		print_info(&ET);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		Quadrangle Q(10, 20, 30, 40, 50, 60, 70, 80);
		print_info(&Q);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		Parallelogram P(10, 20, 50, 60);
		print_info(&P);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		Rectangle R(10, 20);
		print_info(&R);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		Rhomb Rb(10, 50, 60);
		print_info(&Rb);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}
	try {
		Square S(10);
		print_info(&S);
	}
	catch (const FigureCreationException& e) {
		std::cerr << e.what() << "\n" << std::endl;
	}

}