#include "image.h"

Image::Image(int mm, int nn, double h, double w): m(mm), n(nn), height(h), width(w)
{
	int size = mm*nn;
	data = new RGB[size];
	for (int i = 0; i < size; i++) {
		data[i] = RGB();
	}
}

Image::~Image()
{
	delete[] data;
}


inline RGB Image::operator() (int row, int col) const
{
	return data[row*n + col];
}

inline RGB& Image::operator() (int row, int col)
{
	return data[row*n + col];
}


void Image::writeTriangle(ImgTriangle &tri)
{
	double const ep = 0.000001;
	double l1, l2, l3;
	int l, t, r, b;
	l = getMin(tri.x1, tri.x2);
	l = getMin(l, tri.x3);
	t = getMin(tri.y1, tri.y2);
	t = getMin(t, tri.y3);
	r = getMax(tri.x1, tri.x2);
	r = getMax(r, tri.x3);
	b = getMax(tri.y1, tri.y2);
	b = getMax(b, tri.y3);

	// Iterate through the rectangle:
	for (int i = t; i < b; i++) {
		for (int j = l; j < r; j++) {
			//if (i < 0 || j < 0 || i*n+j > m*n)
			//	continue;
			// Calculate the Barycentric Coordinates:
			l1 = (double)( (tri.y2-tri.y3)*(j-tri.x3) + (tri.x3-tri.x2)*(i-tri.y3))
				/ (double) ((tri.y2 - tri.y3)*(tri.x1-tri.x3) + (tri.x3 - tri.x2)*(tri.y1 - tri.y3));
			l2 = (double)( (tri.y3 - tri.y1)*(j - tri.x3) + (tri.x1 - tri.x3)*(i - tri.y3))
				/ (double) ((tri.y3 - tri.y1) * (tri.x2 - tri.x3) + (tri.x1 - tri.x3) * (tri.y2 - tri.y3));
			l3 = 1.0 - l2 - l1;
			// If the pixel is inside the triangle: interpolate and set the value:
			if (l1 >= 0.0-ep && l1 <= 1.0+ep && l2 >= 0.0-ep && l2 <= 1.0+ep && l3 >= 0.0-ep && l3 <= 1.0+ep) {
			//if (l1 >= 0.0 && l1 <= 1.0 && l2 >= 0.0 && l2 <= 1.0 && l3 >= 0.0 && l3 <= 1.0) {
				//cout << i*n+j << endl;
				data[i*n +j].setRedValue(l1*tri.p1.getRedValue() + l2*tri.p2.getRedValue() + l3*tri.p3.getRedValue());
				data[i*n +j].setGreenValue(l1*tri.p1.getGreenValue() + l2*tri.p2.getGreenValue() + l3*tri.p3.getGreenValue());
				data[i*n +j].setBlueValue(l1*tri.p1.getBlueValue() + l2*tri.p2.getBlueValue() + l3*tri.p3.getBlueValue());
			}
		}
	}
}

void Image::writeColormap(Colormap &cmap, const char *filename)
{
	double min = cmap.getMin();
	double max = cmap.getMax();
	double range = max - min;
	double N = (double)n;
	RGB col;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			col = cmap.getJetColor(min + range * j/N);
			data[i*n+j].setRedValue(col.getRedValue());
			data[i*n+j].setGreenValue(col.getGreenValue());
			data[i*n+j].setBlueValue(col.getBlueValue());
		}
	}
}


inline void setRGB(png_byte *ptr, RGB *rgb)
{
	ptr[0] = (int) (rgb->getRedValue() * 255);
	ptr[1] = (int) (rgb->getGreenValue() * 255);
	ptr[2] = (int) (rgb->getBlueValue() * 255);
}

void Image::writeImage(const char *filename)
{
	int code = 0;
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr = 0;
	png_bytep row = 0;

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}
	
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, n, m,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	
	png_write_info(png_ptr, info_ptr);

	row = (png_bytep) malloc(3 * n * sizeof(png_byte));

	int x, y;
	for (y=0 ; y<m; y++) {
		for (x=0 ; x<n; x++) {
			setRGB(&(row[x*3]), &data[y*n+ x]);
		}
		png_write_row(png_ptr, row);
	}

	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

}

