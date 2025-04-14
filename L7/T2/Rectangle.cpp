#include "Figure.h"
#include "Quadrangle.h"
#include "Parallelogram.h"
#include "Rectangle.h"
#include "FigureCreationException.h"


Rectangle::Rectangle(unsigned a, unsigned b) :
	Parallelogram(a, b, 90, 90) {
	name = "Rectangle";
};