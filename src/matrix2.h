#ifndef MATRIX2_H
#define MATRIX2_H

#include <iostream>
#include <cmath>
#include "vertex.h"

using namespace std;

#define EPS 1e-14


class Matrix2
{
	private:
		double *data;
	
	public:
		Matrix2();
		Matrix2(double a, double b, double c, double d);
		Matrix2(const Matrix2 &B);
		// Create the Jacobian Matrix from 3 Points p0, p1, p2:
		Matrix2(Vertex &p0, Vertex &p1, Vertex &p2);
		~Matrix2();

		inline double det()
		{
			return data[0]*data[3] - data[1]*data[2];
		};

		inline double get0() { return *data; };
		inline double get1() { return *(data + 1); };
		inline double get2() { return *(data + 2); };
		inline double get3() { return *(data + 3); };

		void inv();
		void trans();
		Matrix2& operator= (const Matrix2 &B);
		Matrix2 operator* (const Matrix2 &B);
		Matrix2& operator*= (const Matrix2 &B);

		Matrix2& calculateJacobiMatrix(Vertex &p0, Vertex &p1, Vertex &p2);
		inline void getEdgeMatrix(double len)
		{
			data[0] = 1.0/3.0 * len;
			data[1] = 1.0/6.0 * len;
			data[2] = 1.0/6.0 * len;
			data[3] = 1.0/3.0 * len;
		}

		friend ostream& operator<< (ostream &os, Matrix2 &m)
		{
			os << setw(12) << m.get0() << setw(12) << m.get1() << endl;
			os << setw(12) << m.get2() << setw(12) << m.get3() << endl;
			return os;
		}
};

#endif // MATRIX2_H
