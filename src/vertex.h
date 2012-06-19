#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <iomanip>

using namespace std;

class Vertex
{
	private:
		int num;
		double x;
		double y;

		// On which boundary is the Vertex located:
		// 0: Inside Phi
		// 1: Boundary 1
		// 2: Boundary 2
		int loc;

	public:
		Vertex();
		Vertex(double x, double y);
		Vertex(double x, double y, int loc);
		Vertex(int num, double x, double y);
		~Vertex();

		inline void setCoordinates(const double x, const double y) { this->x = x; this->y = y; }
		inline void setLocation(const int loc) { this->loc = loc; }

		inline double getX() const { return this->x; }
		inline double getY() const { return this->y; }
		inline int getLocation() const { return this->loc; }
		inline int getNumber() const { return this->num; }

		Vertex& operator+= (Vertex &p);
		Vertex& operator/= (double d);

		friend ostream& operator<< (ostream &os, Vertex &v)
		{
			os << "Vertex (" << setw(3) << v.num << "): " << "x = " << setw(10) << v.x
				<< ", y = " <<setw(10) << v.y;// << ", Location: " << v.loc;
			return os;
		}

};

#endif // VERTEX_H
