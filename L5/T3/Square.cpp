#include "Figure.h"
#include "Quadrangle.h"
#include "Parallelogram.h"
#include "Rhomb.h"
#include "Square.h"

Square::Square(unsigned a) :
	Rhomb(a, 90, 90) {
	name = "Square";
};