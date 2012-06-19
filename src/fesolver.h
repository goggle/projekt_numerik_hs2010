#ifndef FESOLVER_H
#define FESOLVER_H

#define PI 3.14159265358979323846

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "sparsematrix.h"
#include "vector.h"
#include "dataparser.h"
#include "vertex.h"
#include "element.h"
#include "matrix2.h"
#include "matrix3.h"
#include "plot/image.h"
#include "plot/colormap.h"
#include "plot/rgb.h"
#include "plot/imgtriangle.h"

using namespace std;

class FESolver
{
	public:
		FESolver(string tname, string pname, string bname, double zx0, double zy0, double zx1, double zy1,
			double zx2, double zy2, double zx3, double zy3);
		~FESolver();

		void printMatrix();
		void printVector();
		void printElements();

		void assembly();
		void assemblyBoundaryConditions();

		// Solve the Problem using the implicit Euler and return the time, when 24° C. are reached:
		// The solutions are written to the file 'file'
		double implicitEuler(const char *file);

		void setTriangleColors();
		void writeTriangles();


		inline double fun(double x, double y)
		{
			static const double r2 = 0.04;
			//static const double zx[4] = {0.8, 1.9, 3.0, 4.1};
			//static const double zy[4] = {1.7, 1.7, 1.7, 1.7};
			static double d1;
			static double d2;
			for (int i = 0; i < 4; i++) {
				d1 = (x - zx[i]) * (x - zx[i]);
				d2 = (y - zy[i]) * (y - zy[i]);
				if ((d1 + d2) < r2) {
					return 1000 * sqrt( r2 - d1 - d2 );
				}
			}
			return 0.0;
		}


	private:
		SparseMatrix K; // Global Stiffness Matrix
		SparseMatrix M; // Global Mass Matrix
		Vector l; // Load Vector
		vector<Vertex> points; // List of all the points
		vector<Edge> edges; // List of the edges
		vector<Element> elements; // List of the finite elments

		const double dt; // time step
		const double T_MI; // temperature at the floor
		const double T_BS; // temperature in Basel (December)

		Vector u; // Solution
		Image img; 
		Colormap cmap;
		vector<ImgTriangle> imgtriangles;

		// Positions of the radiators:
		double zx[4];
		double zy[4];

};

#endif // FESOLVER_H
