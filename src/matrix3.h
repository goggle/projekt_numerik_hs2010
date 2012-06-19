#ifndef MATRIX3_H
#define MATRIX3_H

#include<iostream>
#include "matrix2.h"

using namespace std;

class Matrix3
{
	private:
		double *data;

	public:
		Matrix3();
		Matrix3(double a0, double a1, double a2, double a3, double a4, double a5, double a6,
			double a7, double a8);
		~Matrix3();

		Matrix3& createElementMatrix(double area, Matrix2 &J);
		Matrix3& createElementMassMatrix(double k, double detJ);

		inline double get0() { return data[0]; };
		inline double get1() { return data[1]; };
		inline double get2() { return data[2]; };
		inline double get3() { return data[3]; };
		inline double get4() { return data[4]; };
		inline double get5() { return data[5]; };
		inline double get6() { return data[6]; };
		inline double get7() { return data[7]; };
		inline double get8() { return data[8]; };

		Matrix3& operator*= (double a);


		friend ostream& operator<< (ostream &os, Matrix3 &m)
		{
			os << setw(12) << m.data[0] << setw(12) << m.data[1] << setw(12) << m.data[2] << endl;
			os << setw(12) << m.data[3] << setw(12) << m.data[4] << setw(12) << m.data[5] << endl;
			os << setw(12) << m.data[6] << setw(12) << m.data[7] << setw(12) << m.data[8] << endl;
			return os;
		}

};

#endif // MATRIX3_H
