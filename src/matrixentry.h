#ifndef MATRIXENTRY_H
#define MATRIXENTRY_H

#include <iostream>
#include <iomanip>

using namespace std;

class MatrixEntry
{
	public:
		MatrixEntry();
		MatrixEntry(int r, int c, double e);

		inline int getRow() const { return row; };
		inline int getCol() const { return col; };
		inline double getValue() const { return val; };

		inline void setValue(double v) { this->val = v; }
		inline void addValue(double v) { this->val += v; }

		MatrixEntry operator+ (const MatrixEntry &e);
		MatrixEntry& operator+= (const MatrixEntry &e);

		friend ostream& operator<< (ostream &os, MatrixEntry &entry)
		{
			os << "row: " << setw(3) << entry.getRow() << ", col: " << setw(3) 
				<< entry.getCol() << ", val = " << setw(7) <<  entry.getValue();
			return os;
		}
		

	private:
		int row;
		int col;
		double val;

};

#endif
