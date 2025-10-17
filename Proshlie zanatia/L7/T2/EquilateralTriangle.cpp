#include "Figure.h"
#include "Triangle.h"
#include "IsoscelesTriangle.h"
#include "EquilateralTriangle.h"
#include "FigureCreationException.h"


EquilateralTriangle::EquilateralTriangle(unsigned a) :
	IsoscelesTriangle(a, a, 60, 60) {
	name = "EquilateralTriangle";
};