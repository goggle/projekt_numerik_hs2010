#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include "vertex.h"

class Element
{
	public:
		Element();
		Element(Vertex &v1, Vertex &v2, Vertex &v3);

		friend ostream& operator<< (ostream &os, Element &elem) {
			os << "Triangle Element:" << endl;
			os << *(elem.point1) << endl;
			os << *(elem.point2) << endl;
			os << *(elem.point3) << endl;
			return os;
		}

		Vertex getMiddlePoint();

		inline Vertex& getPoint1() { return *point1; };
		inline Vertex& getPoint2() { return *point2; };
		inline Vertex& getPoint3() { return *point3; };

	private:
		Vertex *point1;
		Vertex *point2;
		Vertex *point3;

};

#endif // ELEMENT_H
