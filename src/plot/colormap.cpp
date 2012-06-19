#include "colormap.h"

Colormap::Colormap(): min(0.0), max(0.0) {}
Colormap::Colormap(double min_, double max_): min(min_), max(max_) {}

RGB Colormap::getColor(double val)
{
	double r, g, b;
	double middle = 0.5 * (min + max);
	double range;
	RGB col;
	if (val >= max) {
		col.setValue(1.0, 0.0, 0.0);
	}
	else if (val <= min) {
		col.setValue(0.0, 0.0, 1.0);
	}
	else if (val >= middle) {
		range = max - middle;
		r = 1.0;
		b = 0.0;
		g = 1.0 -  (val-middle)/range;
		col.setValue(r, g, b);
	}
	else {
		range = middle - min;
		r = (val-min) / range;
		g = (val-min) / range;
		b = 1.0 - (val-min) / range;
		col.setValue(r, g, b);
	}
	return col;
}

/*
 * The Jet Colormap: 
 */
RGB Colormap::getJetColor(double val)
{
	double r, g, b;
	double v;
	RGB col;

	if (val <= min)
		v = 0.0;
	else if (val >= max)
		v = 1.0;
	else {
		// Normalize:
		v = (val - min) / (max - min);
	}

	if (v >= 0.0 && v < 0.35)
		r = 0.0;
	else if (v >= 0.35 && v < 0.66)
		r = (v - 0.35) / (0.66 - 0.35);
	else if (v >= 0.66 && v < 0.89)
		r = 1.0;
	else
		r = 1.0 + (-0.5)/(1.0-0.89) * (v - 0.89);

	if (v >= 0.0 && v < 0.125)
		g = 0.0;
	else if (v >= 0.125 && v < 0.375)
		g = 1.0/(0.375 - 0.125) * (v - 0.125);
	else if (v >= 0.375 && v < 0.64)
		g = 1.0;
	else if (v >= 0.64 && v < 0.91)
		g = 1.0 + (-1)/(0.91 - 0.64) * (v - 0.64);
	else
		g = 0.0;

	if (v >= 0.0 && v < 0.11)
		b = 0.5 + 0.5/0.11 * v;
	else if (v >= 0.11 && v < 0.34)
		b = 1.0;
	else if (v >= 0.34 && v < 0.65)
		b = 1 + (-1)/(0.65 - 0.34) * (v - 0.34);
	else
		b = 0.0;

	col.setValue(r, g, b);
	return col;

}
