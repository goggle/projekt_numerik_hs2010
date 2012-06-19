#ifndef IMGTRIANGLE_H
#define IMGTRIANGLE_H

#include <iostream>
#include <cmath>
#include "rgb.h"

using namespace std;

class ImgTriangle
{
	public:
		ImgTriangle();
		ImgTriangle(double, double, double, double, double, double);

		inline void setCoordinates(int m, int n, double height, double width)
		{
			x1 = (double)(n)/(double)width * xd1;
			y1 = m - (double)(m)/(double)height * yd1;
			x2 = (double)(n)/(double)width * xd2;
			y2 = m - (double)(m)/(double)height * yd2;
			x3 = (double)(n)/(double)width * xd3;
			y3 = m - (double)(m)/(double)height * yd3;
		}
		inline void setP1(RGB p1) { this->p1 = p1; };
		inline void setP2(RGB p2) { this->p2 = p2; };
		inline void setP3(RGB p3) { this->p3 = p3; };



		int x1, y1;
		int x2, y2;
		int x3, y3;
		double xd1, yd1;
		double xd2, yd2;
		double xd3, yd3;
		RGB p1;
		RGB p2;
		RGB p3;

};

#endif
