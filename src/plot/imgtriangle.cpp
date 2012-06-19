#include "imgtriangle.h"

ImgTriangle::ImgTriangle():
	x1(0), y1(0), x2(0), y2(0), x3(0), y3(0),
	xd1(0.0), yd1(0.0), xd2(0.0), yd2(0.0), xd3(0.0), yd3(0.0) {}

ImgTriangle::ImgTriangle(double a1, double b1, double a2, double b2, double a3, double b3):
	x1(0), y1(0), x2(0), y2(0), x3(0), y3(0),
	xd1(a1), yd1(b1), xd2(a2), yd2(b2), xd3(a3), yd3(b3) {}
