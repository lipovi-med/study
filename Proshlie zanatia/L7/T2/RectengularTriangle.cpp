#include "Figure.h"
#include "Triangle.h"
#include "RectengularTriangle.h"
#include "FigureCreationException.h"

RectengularTriangle::RectengularTriangle(unsigned a, unsigned b, unsigned c, unsigned A, unsigned B) :
	Triangle(a, b, c, A, B, 90) {
	if (A + B != 90) {
		throw FigureCreationException("Ошибка создания фигуры. Причина: сумма углов A и B не равна 90.");
	}
	name = "RectengularTriangle";
	}