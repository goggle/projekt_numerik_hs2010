#ifndef COLORMAP_H
#define COLORMAP_H

#include <iostream>
#include "rgb.h"

using namespace std;

class Colormap
{
	public:
		Colormap();
		Colormap(double min_, double max_);
		
		RGB getColor(double val);
		RGB getJetColor(double val);
		inline double getMin() { return min; };
		inline double getMax() { return max; };

	private:
		double min;
		double max;

};

#endif // COLORMAP_H
