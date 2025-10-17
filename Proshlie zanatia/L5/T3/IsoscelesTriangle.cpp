#include "Figure.h"
#include "Triangle.h"
#include "IsoscelesTriangle.h"

IsoscelesTriangle::IsoscelesTriangle(unsigned a, unsigned b, unsigned A, unsigned B) :
	Triangle(a, b, a, A, B, A) {
	name = "IsoscelesTriangle";
};