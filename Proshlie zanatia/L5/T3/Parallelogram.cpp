#include "Figure.h"
#include "Quadrangle.h"
#include "Parallelogram.h"

Parallelogram::Parallelogram(unsigned a, unsigned b, unsigned A, unsigned B) :
	Quadrangle(a, b, a, b, A, B, A, B) {
	name = "Parallelogram";
};