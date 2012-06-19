#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <malloc.h>
#include <zlib.h>
#include <png.h>
#include "rgb.h"
#include "imgtriangle.h"
#include "colormap.h"

using namespace std;

class Image
{
	public:
		Image(int m, int n, double height, double width);
		~Image();
		RGB operator() (int row, int col) const;
		RGB& operator() (int row, int col);
	
		inline int getM() { return m; };
		inline int getN() { return n; };
		inline double getHeight() { return height; };
		inline double getWidth() { return width; };
		void writeTriangle(ImgTriangle &t);
		void writeImage(const char *filename);
		void writeColormap(Colormap &cmap, const char *filename);


	private:
		int m;
		int n;
		double height;
		double width;
		RGB *data;

		inline int getMin(int x, int y) { return x <= y ? x : y; };
		inline int getMax(int x, int y) { return x > y ? x : y;};



};

#endif //IMAGE_H
