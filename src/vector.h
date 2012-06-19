#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iomanip>
#include <cmath>

#include "element.h"
#include "edge.h"

using namespace std;


class Vector
{
	private:
		int ndim;
		double *data;
	
	public:
		Vector();
		Vector(int m);
		Vector(const Vector& v); // Copy-constructor
		Vector(double a, double b, double c); // Constructor for a 3D Vector
		~Vector();

		// Access operator: Valid range is not checked!
		double operator[](int index) const
		{
			#ifndef NDEBUG
			if (index < 0 || index >= ndim)
				cerr << "Vector: Out of range!" << endl;
			#endif
			return data[index];
		};
		
		Vector& operator= (const Vector& v); // assignment operator
		Vector operator* (const double alpha); // multiplication by scalar
		inline double operator* (const Vector& v) { // standard dot product
			double dot = 0.0;
			for (int i = 0; i < ndim ; i++) {
				dot += (data[i] * v.data[i]);
			}
			return dot;
		}
		Vector operator+ (const Vector& v);
		Vector& operator+= (const Vector& v);
		Vector operator- (const Vector &v);
		Vector& operator-= (const Vector &v);
		inline Vector& vecmul(const Vector &v1, const Vector &v2)
		{
			#ifndef NDEBUG
			if (v1.getDim() != v2.getDim()) {
				cerr << "Error in vecmul(): Dimension mismatch!" << endl;
				return *this;
			}
			#endif
			for (int i = 0; i < ndim; i++) {
				data[i] = v1[i] * v2[i];
			}
			return *this;
		}

		inline int getDim() const { return ndim; }
		inline void setEntry(int ind, double entry) const { data[ind] = entry; }
		double getMean();
		
		// Add the Vector a*p to the existing Vector (needed for Conjugate Gradient):
		inline Vector& addVectorMultByScalar(const double a, const Vector &p) {
			for (int i = 0; i < ndim; i++) {
				data[i] += a*p.data[i];
			}
			return *this;
		}
		
		// Muliply this Vector by the Scalar d and add the Vector r (needed for Conjugate Gradient):
		inline Vector& multByScalarAddVector(const double b, const Vector &r) {
			for (int i = 0; i < ndim; i++) {
				data[i] = r.data[i] + b*data[i];
			}
			return *this;
		}

		// Assign x1 + alpha*x2 to this Vector (needed for CGS):
		inline Vector assignVec1PlusVec2MultByScalar(const Vector &x1, const double a, const Vector &x2)
		{
			for (int i = 0; i < ndim; i++) {
				data[i] = x1.data[i] + a * x2.data[i];
			} 
			return *this;
		}

		// Last step in CGS:
		inline Vector& updateP(const double a, const double b, const Vector &x1, const Vector &x2, const Vector &x3)
		{
			for (int i = 0; i < ndim; i++) {
				data[i] = x1.data[i] + a * ( x2.data[i] + b * x3.data[i] );
			}
			return *this;
		}

		double norm(); // euclidean norm
		
		void createElementVector(double f, double detJ);
		void addElementVector(Element &elem, Vector &lel);
		void addEdgeCondition(Edge &edge, double len, double temperature);

		// Solve the Linear System Ax=b using the Conjugate Gradient method:
		//Vector& conjugateGradient(const SparseMatrix &A, const Vector &b);

		//friend ostream& operator<< (ostream &os, Vector &vec)
		//{
		//	os << endl;
		//	for (int i = 0; i < vec.ndim; i++) {
		//		os << setw(10) << vec.data[i] << endl;
		//	}
		//	return os;
		//}


		friend ostream& operator<< (ostream &os, Vector &vec)
		{
			for (int i = 0; i < vec.ndim; i++) {
				os << vec.data[i] << setw(10);
			}
			return os;
		}
};

#endif // VECTOR_H
