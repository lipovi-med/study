#include "Figure.h"
#include "Triangle.h"
#include "RectengularTriangle.h"

RectengularTriangle::RectengularTriangle(unsigned a, unsigned b, unsigned c, unsigned A, unsigned B) :
	Triangle(a, b, c, A, B, 90) {
	name = "RectengularTriangle";
	}