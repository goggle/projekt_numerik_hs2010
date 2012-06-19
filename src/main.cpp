#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
	int n = 3;
	Vector vec(n);
	
	double dot = vec * vec;

	cout << vec[0] << " " << vec[1] << " " <<  vec[2] <<  endl;
	cout << dot << endl;

	vec = vec*2;

	cout << vec[0] << " " << vec[1] << " " <<  vec[2] <<  endl;

	vec = vec + vec;
	cout << vec[0] << " " << vec[1] << " " <<  vec[2] <<  endl;

	double norm = vec.norm();
	cout << norm << endl;
	
	cout << endl << endl;
	vec.setEntry(0, 100);
	cout << vec << endl;

	Vector x(4);
	x.setEntry(0,1);
	x.setEntry(1,3);
	x.setEntry(2,1.5);
	x.setEntry(3,5);

	cout << x << endl;

	Vector y(4);
	y.setEntry(0,1);
	y.setEntry(1,1);
	y.setEntry(2,1);
	y.setEntry(3,1);

	cout << x*y << endl;

	//x.addVectorMultByScalar(2.0, y);
	//cout << x << endl;

	x.multByScalarAddVector(2.5, y);
	cout << x << endl;


	return 0;
}

