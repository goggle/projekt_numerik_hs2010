#ifndef RGB_H
#define RGB_H

#include <iostream>

using namespace std;

class RGB
{
	public:
		RGB();
		RGB(double r, double g, double b);
		inline void setValue(double r, double g, double b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
		inline double getRedValue()
		{
			return this->r;
		}
		inline double getGreenValue()
		{
			return this->g;
		}
		inline double getBlueValue()
		{
			return this->b;
		}
		inline void setRedValue(double red) { r = red; };
		inline void setGreenValue(double green) { g = green; };
		inline void setBlueValue(double blue) { b = blue; };

		friend ostream& operator<< (ostream &os, RGB &rgb)
		{
			os << "(" << rgb.getRedValue() << ", " << rgb.getGreenValue() << ", " << rgb.getBlueValue() << ")";
			return os;
		}


	private:
		double r;
		double g;
		double b;

};

#endif // RGB_H
