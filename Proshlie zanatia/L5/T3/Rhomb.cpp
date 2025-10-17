#include "Figure.h"
#include "Quadrangle.h"
#include "Parallelogram.h"
#include "Rhomb.h"


Rhomb::Rhomb(unsigned a, unsigned A, unsigned B) :
	Parallelogram(a, a, A, B) {
	name = "Rhomb";
};