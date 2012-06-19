#include "matrix2.h"

Matrix2::Matrix2()
{
	data = new double[4];
	for (int i = 0; i < 4; i++)
		data[i] = 0.0;

	#ifndef NDEBUG
	cout << "2x2 Matrix created." << endl;
	#endif
}

Matrix2::Matrix2(double a, double b, double c, double d)
{
	data = new double[4];
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	#ifndef NDEBUG
	cout << "2x2 Matrix created." << endl;
	#endif
}

Matrix2::Matrix2(const Matrix2 &B)
{
	data[0] = B.data[0];
	data[1] = B.data[1];
	data[2] = B.data[2];
	data[3] = B.data[3];
}

Matrix2::Matrix2(Vertex &p0, Vertex &p1, Vertex &p2)
{
	data = new double[4];
	double x0 = p0.getX();
	double y0 = p0.getY();
	data[0] = p1.getX() - x0;
	data[2] = p1.getY() - y0;
	data[1] = p2.getX() - x0;
	data[3] = p2.getY() - y0;
	#ifndef NDEBUG
	cout << "2x2 Jacobi Matrix created." << endl;
	#endif
}


Matrix2::~Matrix2()
{
	delete[] data;
}

Matrix2& Matrix2::calculateJacobiMatrix(Vertex &p0, Vertex &p1, Vertex &p2)
{
	double x0 = p0.getX();
	double y0 = p0.getY();
	data[0] = p1.getX() - x0;
	data[2] = p1.getY() - y0;
	data[1] = p2.getX() - x0;
	data[3] = p2.getY() - y0;
	return *this;
}


/*
 Invert this Matrix:
*/
void Matrix2::inv()
{
	#ifndef NDEBUG
	double determinant = det();
	if (abs(determinant) < EPS) {
		cerr << "Error: Matrix is singular!" << endl;
		return;
	}
	#endif
	double f = 1./det();
	double a,b,c,d;
	a = f*data[3];
	b = -f*data[1];
	c = -f*data[2];
	d = f*data[0];
	// TODO: optimize
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	//Matrix2 invMat(a, b, c, d);
	//return invMat;
}

/*
 Transpose this Matrix:
*/
void Matrix2::trans()
{
	//Matrix2 transMat(data[1], data[3], data[2], data[4]);
	//return transMat;
	double tmp = data[1];
	data[1] = data[2];
	data[2] = tmp;
}

Matrix2& Matrix2::operator= (const Matrix2 &B)
{
	if (this == &B)
		return *this;

	data[0] = B.data[0];
	data[1] = B.data[1];
	data[2] = B.data[2];
	data[3] = B.data[3];

	return *this;
}

// TODO: optimize...
Matrix2 Matrix2::operator* (const Matrix2 &B)
{
	double a,b,c,d;
	a = data[0]*B.data[0] + data[1]*B.data[2];
	b = data[0]*B.data[1] + data[1]*B.data[3];
	c = data[2]*B.data[0] + data[3]*B.data[2];
	d = data[2]*B.data[1] + data[3]*B.data[3];
	Matrix2 R(a,b,c,d);
	return R;
}

Matrix2& Matrix2::operator*= (const Matrix2 &B)
{
	double a,b,c,d;
	a = data[0]*B.data[0] + data[1]*B.data[2];
	b = data[0]*B.data[1] + data[1]*B.data[3];
	c = data[2]*B.data[0] + data[3]*B.data[2];
	d = data[2]*B.data[1] + data[3]*B.data[3];
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	return *this;
}

