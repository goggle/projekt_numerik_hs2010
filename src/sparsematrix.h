#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#define ZERO_EPS 1e-15

#include <iostream>
#include <list>
#include <vector>
#include <cmath>

#include "matrixentry.h"
#include "vector.h"
#include "matrix3.h"
#include "element.h"
#include "edge.h"


using namespace std;


class SparseMatrix
{
	public:
		SparseMatrix();
		SparseMatrix(int s);
		SparseMatrix(const SparseMatrix &M);
		~SparseMatrix();

		void setEntry(int i, int j, double val);
		void addEntry(int i, int j, double val);
		double getValue(const int i, const int j) const;
		inline int getSize() const { return this->size; };
		inline list<MatrixEntry*> getRowList(int k) const { return rows[k]; };
		inline list<MatrixEntry*> getColList(int k) const { return cols[k]; };

		void printViaRows();
		void printViaColumns();

		void addElementMatrix(Element &elem, Matrix3 &Ael);
		void addEdgeMatrix(Edge &edge, Matrix2 &M);

		// Solve Linear System Ax=b using the Conjugate Gradient method:
		Vector conjugateGradient(const Vector &b);
		Vector conjugateGradientInnerPoints(const Vector &b, const vector<Vertex> &points);
		Vector cgs(const Vector &b);
		Vector getJacobiPreconditioner();
		Vector preconditionedConjugateGradient(const Vector &b);

		SparseMatrix& operator= (const SparseMatrix &mat);
		SparseMatrix& operator*= (const double a);

		// Multiply Sparse Matrix with Vector:
		Vector operator* (const Vector &x);
		Vector& multiplyVector(const Vector &x, Vector &res);
		Vector matmul (const Vector &x, const vector<int> &innerpoints);

		SparseMatrix operator+ (const SparseMatrix &mat);

		friend ostream& operator<< (ostream &os, SparseMatrix &mat) {
			list<MatrixEntry*> *rowlist;
			list<MatrixEntry*>::iterator iter;
			for (int i = 0; i < mat.size; i++) {
				rowlist = &(mat.rows[i]);
				for (iter = rowlist->begin(); iter != rowlist->end(); iter++) {
					os << **iter << endl;
				}
			}
			return os;
		}



	private:
		int size;
		list<MatrixEntry*> *rows; // Array containing in each field a List of pointers to the matrix entries.
		list<MatrixEntry*> *cols;

};

#endif //SPARSEMATRIX_H
