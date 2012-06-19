#include "matrixentry.h"


MatrixEntry::MatrixEntry(): row(0), col(0), val(0) {}
MatrixEntry::MatrixEntry(int r, int c, double e):
	row(r), col(c), val(e) {}

MatrixEntry MatrixEntry::operator+ (const MatrixEntry &e)
{
	#ifndef NDEBUG
	if (row != e.row || col != e.col) {
		cout << "Warning: Columns or rows in Entry addition do not match!" << endl;
	}
	#endif
	MatrixEntry entry = MatrixEntry(row, col, 0);
	entry.val = val + e.val;
	return entry;
}

MatrixEntry& MatrixEntry::operator+= (const MatrixEntry &e)
{
	#ifndef NDEBUG
	if (row != e.row || col != e.col) {
		cout << "Warning: Columns or rows in Entry addition do not match!" << endl;
	}
	#endif
	val += e.val;
	return *this;
}



