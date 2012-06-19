#include "matrix3.h"

Matrix3::Matrix3()
{
	data = new double[9];
	for (int i = 0; i < 9; i ++) {
		data[i] = 0.0;
	}
	#ifndef NDEBUG
	cout << "3x3 Matrix created." << endl;
	#endif
}

Matrix3::Matrix3(double a0, double a1, double a2, double a3, double a4, double a5, double a6,
	double a7, double a8)
{
	data = new double[9];
	data[0] = a0;
	data[1] = a1;
	data[2] = a2;
	data[3] = a3;
	data[4] = a4;
	data[5] = a5;
	data[6] = a6;
	data[7] = a7;
	data[8] = a8;
	#ifndef NDEBUG
	cout << "3x3 Matrix created." << endl;
	#endif
}

Matrix3::~Matrix3()
{
	delete[] data;
}


Matrix3& Matrix3::operator*= (double a)
{
	data[0] *= a;
	data[1] *= a;
	data[2] *= a;
	data[3] *= a;
	data[4] *= a;
	data[5] *= a;
	data[6] *= a;
	data[7] *= a;
	data[8] *= a;
	return *this;
}


Matrix3& Matrix3::createElementMatrix(double area, Matrix2 &J) 
{
	J.inv(); // TODO: direct calculation
	double a0 = J.get0();
	double a1 = J.get1();
	double a2 = J.get2();
	double a3 = J.get3();
	double a00 = a0*a0;
	double a02 = a0*a2;
	double a11 = a1*a1;
	double a13 = a1*a3;
	double a22 = a2*a2;
	double a33 = a3*a3;
	data[0] = area * (a00 + 2*a02 + a22 + a11 + 2*a13 + a33 );
	data[1] = area * (-a00 - a02 - a11 - a13 );
	data[2] = area * (-a02 - a22 - a13 - a33 );
	data[3] = area * (-a00 - a02 - a11 - a13);
	data[4] = area * (a00 + a11);
	data[5] = area * (a02 + a13);
	data[6] = area * (-a02 - a22 - a13 - a33);
	data[7] = area * (a02 + a13);
	data[8] = area * (a22 + a33);
	
	return *this;
}


Matrix3& Matrix3::createElementMassMatrix(double k, double detJ)
{
	double koeff = k * abs(detJ);
	data[0] = 2 * koeff;
	data[1] = 1 * koeff;
	data[2] = 1 * koeff;
	data[3] = 1 * koeff;
	data[4] = 2 * koeff;
	data[5] = 1 * koeff;
	data[6] = 1 * koeff;
	data[7] = 1 * koeff;
	data[8] = 2 * koeff;
	return *this;
}
