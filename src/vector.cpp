#include "vector.h"

// Standard constructor:
Vector::Vector(): ndim(0) {
	#ifndef NDEBUG
	cout << "Empty Vector created" << endl;
	#endif
}

Vector::Vector(int m): ndim(m)
{
	data = new double[m];

	for (int i = 0; i < ndim; i++)
		data[i] = 0.0;
	
	#ifndef NDEBUG
	cout << "New Vector with " << m << " entries created." << endl;
	#endif
}

Vector::Vector(double a, double b, double c) : ndim(3)
{
	data = new double[3];
	data[0] = a;
	data[1] = b;
	data[2] = c;

	#ifndef NDEBUG
	cout << "3d Vector created." << endl;
	#endif
}

// Copy constructor:
Vector::Vector(const Vector& v) 
{
	#ifndef NDEBUG
	cout << "Vector copy constructor..." << endl;
	#endif
	ndim = v.ndim;
	data = new double[ndim];
	for (int i = 0; i < ndim; i++)
		data[i] = v.data[i];
}

// Destructor:
Vector::~Vector() 
{
	if (ndim != 0) {
		delete[] data;
		#ifndef NDEBUG
		cout << "Vector with " << ndim << " entries deleted."  << endl;
		#endif
	}
	else {
	#ifndef NDEBUG
	cout << "Empty Vector deleted." << endl;
	#endif
	}
}

// Assignment operator:
Vector& Vector::operator= (const Vector& v)
{
	#ifndef NDEBUG
	cout << "Vector assignment." << endl;
	#endif
	if (this == &v)
		return *this;
	if (ndim != 0)
		delete[] data;
	
	ndim = v.ndim;
	data = new double[ndim];
	for (int i = 0; i < ndim; i++)
		data[i] = v.data[i];
	return *this;
}


Vector Vector::operator* (const double alpha)
{
	Vector vec(ndim);
	for (int i = 0; i < ndim; i++)
		vec.data[i] = alpha * data[i];
	return vec;
}

//double Vector::operator* (const Vector &v)
//{
//	double dot = 0.0;
//	for (int i = 0; i < ndim; i++)
//		dot += data[i] * v.data[i];
//	return dot;
//}

Vector Vector::operator+ (const Vector& v)
{
	Vector vecadd(ndim);
	for (int i = 0; i < ndim; i++)
		vecadd.data[i] = data[i] + v.data[i];
	return vecadd;
}

Vector& Vector::operator+= (const Vector &v)
{
	for (int i = 0; i < ndim; i++) {
		data[i] += v.data[i];
	}
	return *this;
}

Vector Vector::operator- (const Vector &v) {
	Vector vec(ndim);
	for (int i = 0; i < ndim; i++) {
		vec.data[i] = data[i] - v.data[i];
	}
	return vec;
}

Vector& Vector::operator-= (const Vector &v) {
	for (int i = 0; i < ndim; i++) {
		data[i] -= v.data[i];
	}
	return *this;
}

//ostream& operator<< (ostream& os, Vector const &v)
//{
//	int n = v.getDim();
//	for (int i = 0; i < n; i++) {
//		os << v[i];
//	}
//	return os;
//}
	

//void Vector::setEntry(int ind, double entry)
//{
//	data[ind] = entry;
//	//*(data+ind) = entry;
//}

double Vector::norm()
{
	return sqrt( (*this) * (*this) );
}


void Vector::createElementVector(double f, double detJ)
{
	#ifndef NDEBUG
	if (ndim != 3)
		cerr << "Error in createElementVector(): Element Load Vector must have size 3!" << endl;
	#endif
	data[0] = data[1] = data[2] = f/6 * abs(detJ);
}

void Vector::addElementVector(Element &elem, Vector &lel)
{
	#ifndef NDEBUG
	if (lel.ndim != 3)
		cerr << "Error in addElementVector(): Element Load Vector must have size 3!" << endl;
	#endif
	int p0, p1, p2;
	p0 = elem.getPoint1().getNumber() - 1;
	p1 = elem.getPoint2().getNumber() - 1;
	p2 = elem.getPoint3().getNumber() - 1;

	data[p0] += lel[0];
	data[p1] += lel[1];
	data[p2] += lel[2];
	
}

void Vector::addEdgeCondition(Edge &edge, double len, double temperature)
{
	int p0, p1;
	p0 = edge.getPoint1().getNumber() - 1;
	p1 = edge.getPoint2().getNumber() - 1;

	data[p0] += 0.5 * len * temperature;
	data[p1] += 0.5 * len * temperature;
}

double Vector::getMean()
{
	double sum = 0.0;
	for (int i = 0; i < ndim; i++) {
		sum += data[i];
	}
	return sum / ndim;
}


