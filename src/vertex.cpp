#include "vertex.h"

Vertex::Vertex(): num(0), x(0), y(0), loc(0) {}
Vertex::Vertex(double a, double b): num(0), x(a), y(b), loc(0) {}
Vertex::Vertex(double a, double b, int c): num(0), x(a), y(b), loc(c) {}
Vertex::Vertex(int a, double b, double c): num(a), x(b), y(c), loc(0) {}
Vertex::~Vertex(){}

Vertex& Vertex::operator+= (Vertex &p)
{
	x += p.x;
	y += p.y;
	return *this;
}


Vertex& Vertex::operator/= (double d)
{
	x /= d;
	y /= d;
	return *this;
}
