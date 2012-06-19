#include <iostream>
#include <vector>

#include "matrixentry.h"
#include "sparsematrix.h"
#include "vector.h"

using namespace std;

int main()
{
	//MatrixEntry entry1 = MatrixEntry(1,1,5);
	//cout << entry1 << endl;

	//MatrixEntry entry2 = MatrixEntry(1,1,6);
	//cout << entry2 << endl;

	//MatrixEntry entry3 = entry1 + entry2;
	//cout << entry3 << endl;

//	SparseMatrix mat = SparseMatrix(20);
//	mat.setEntry(1,1,5);
//	mat.setEntry(1,4,5);
//	mat.setEntry(1,4,8);
//	mat.setEntry(1,17, 0.5);
//	mat.setEntry(1,14, 0.25);
//	mat.setEntry(2,0,0.2);
//	mat.setEntry(1,12,1);
//	mat.setEntry(1,0,1.11);
//	mat.setEntry(3,12,1);
//	mat.setEntry(2,12,2);
//	mat.setEntry(14,12,0.1);
//	mat.printViaRows();
//
//	cout << endl << endl;
//	mat.printViaColumns();
//
//	cout << endl << endl;
//	cout << mat.getValue(1,1) << endl;
//	cout << mat.getValue(3,12) << endl;
//	cout << mat.getValue(1,17) << endl;
//	cout << mat.getValue(14,12) << endl;
//	cout << mat.getValue(1,5) << endl;
//
//	cout << endl << endl;
//	cout << mat << endl;
//
//	Vector x = Vector(4);
//	x.setEntry(0,1);
//	x.setEntry(1,2);
//	x.setEntry(2,5);
//	x.setEntry(3,2.5);

	SparseMatrix A = SparseMatrix(4);
	A.setEntry(0,0,1);
	A.setEntry(1,1,1);
	A.setEntry(2,2,1);
	A.setEntry(3,3,1);
	A.setEntry(0,1,2);
	A.setEntry(1,2,2);
	A.setEntry(2,3,2);
	A.setEntry(1,0,2);
	A.setEntry(2,1,2);
	A.setEntry(3,2,2);

	
//	Vector s = A.conjugateGradient(x);
//	cout << s << endl;
//
//	x = Vector(2);
//	x.setEntry(0,2);
//	x.setEntry(1,3);
//
//	vector<int> ip;
//	ip.push_back(1);
//	ip.push_back(3);
//
//
//	//Vector res = A.matmul(x, ip);
//	//cout << res << endl;
//	
//	SparseMatrix B = SparseMatrix(4);
//	B.setEntry(0,0, 10);
//	B.setEntry(0,3, 5);
//	B.setEntry(2,2, 3);
//	B.setEntry(2,3, 3);
//	B.setEntry(3,1, 2);
////	cout << B << endl;
////
//	SparseMatrix C;
//	C = A + B;
//	cout << C << endl;
////
//
//	SparseMatrix D(4);
//	D.setEntry(0,0,11);
//	D.setEntry(0,1,2);
//	D.setEntry(0,3,5);
//	D.setEntry(1,0,2);
//	D.setEntry(1,1,1);
//	D.setEntry(1,2,2);
//	D.setEntry(2,1,2);
//	D.setEntry(2,2,4);
//	D.setEntry(2,3,5);
//	D.setEntry(3,1,2);
//	D.setEntry(3,2,2);
//	D.setEntry(3,3,1);
//	cout << D << endl;
//	SparseMatrix E;
//	E = D;
//	cout << E << endl;
//
//	SparseMatrix F;
//	F = D + E;
//	cout << F << endl;


	Vector l(4);
	l.setEntry(0,1);
	l.setEntry(1,2);
	l.setEntry(2,-1);
	l.setEntry(3,-3);
	cout << A << endl;
	Vector x;
	x = A.cgs(l);
	cout << x << endl;

	cout << A << endl;
	A *= 0.5;
	cout << A << endl;


	return 0;
}
