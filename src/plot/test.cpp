#include <iostream>
#include <png.h>
#include "image.h"
#include "imgtriangle.h"
#include "rgb.h"
#include "colormap.h"

using namespace std;

int main()
{
	Image img(400, 1000, 2.0, 5.0);
	char filename[] = "hello.png";

	RGB col1(0.9, 0.0, 0.0);
	RGB col2(0.0, 0.9, 0.0);
	RGB col3(0.0, 0.0, 0.9);
	ImgTriangle tri(0.1,0.1, 4.5, 0.2, 3.5, 1.4);
	tri.setCoordinates(400, 1000, 2.0, 5.0);
	tri.setP1(col1);
	tri.setP2(col2);
	tri.setP3(col3);

	cout << "(" << tri.x1 <<", " << tri.y1 << ")" << endl;
	cout << "(" << tri.x2 <<", " << tri.y2 << ")" << endl;
	cout << "(" << tri.x3 <<", " << tri.y3 << ")" << endl;

	//img.writeTriangle(tri);
	//img.writeImage(filename);

	Colormap cmap(14, 28);
	img.writeColormap(cmap, filename);
	img.writeImage(filename);

	


	return 0;
}

