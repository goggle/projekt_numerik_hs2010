#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <cmath>
#include "vertex.h"

class Edge
{
	public:
		Edge();
		Edge(Vertex &v1, Vertex &v2);
		Edge(Vertex &v1, Vertex &v2, int l);

		friend ostream& operator<< (ostream &os, Edge &elem) {
			os << "Edge:" << endl;
			os << "Location: " << elem.getLocation() << endl;
			os << *(elem.point1) << endl;
			os << *(elem.point2) << endl;
			return os;
		}

		inline Vertex& getPoint1() { return *point1; };
		inline Vertex& getPoint2() { return *point2; };
		inline int getLocation() { return loc; };
		inline double getLength()
		{
			double x1, x2, y1, y2;
			double a, b;
			x1 = point1->getX();
			y1 = point1->getY();
			x2 = point2->getX();
			y2 = point2->getY();
			a = (x2 - x1) * (x2 - x1);
			b = (y2 - y1) * (y2 - y1);
			return sqrt(a+b);
		}
			

	private:
		Vertex *point1;
		Vertex *point2;

		// On which boundary is the edge located:
		// 0: Wall
		// 1: Door
		// 2: Window
		int loc;

};

#endif // EDGE_H
