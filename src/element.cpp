#include "element.h"

Element::Element(): point1(NULL), point2(NULL), point3(NULL) {}
Element::Element(Vertex &v1, Vertex &v2, Vertex &v3):
	point1(&v1), point2(&v2), point3(&v3)
{
}

Vertex Element::getMiddlePoint()
{
	Vertex m = Vertex();
	m += *point1;
	m += *point2;
	m += *point3;
	m /= 3;
	return m;
}


	


