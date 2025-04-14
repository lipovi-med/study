#include "Figure.h"
#include "Triangle.h"
#include "IsoscelesTriangle.h"
#include "FigureCreationException.h"

IsoscelesTriangle::IsoscelesTriangle(unsigned a, unsigned b, unsigned A, unsigned B) :
	Triangle(a, b, a, A, B, A) {
	if (A != B) {
		throw FigureCreationException("������ �������� ������. �������: ���� A � B ������ ���� �����.");
	}
	name = "IsoscelesTriangle";
};