#include <iostream>
#include <cstdlib>
#include "matrixentry.h"
#include "sparsematrix.h"
#include "vector.h"

#include "fesolver.h"

using namespace std;

int main(int argc, char *argv[])
{
	string tname("t_grob.dat");
	string pname("p_grob.dat");
	string bname("b_grob.dat");
	double zx1, zy1, zx2, zy2, zx3, zy3, zx4, zy4;
	if (argc == 9){
		zx1 = atof(argv[1]);
		zy1 = atof(argv[2]);
		zx2 = atof(argv[3]);
		zy2 = atof(argv[4]);
		zx3 = atof(argv[5]);
		zy3 = atof(argv[6]);
		zx4 = atof(argv[7]);
		zy4 = atof(argv[8]);
	}
	else {
		zx1 = 0.8; zy1 = 1.7;
		zx2 = 1.9; zy2 = 1.7;
		zx3 = 3.0; zy3 = 1.7;
		zx4 = 4.1; zy4 = 1.7;
	}
	FESolver solver = FESolver(tname, pname, bname, zx1, zy1, zx2, zy2, zx3, zy3, zx4, zy4);
	solver.assembly();
	solver.assemblyBoundaryConditions();
	double time = solver.implicitEuler("../data/u_grob.dat");
	cout << "Zeit bis zum Erreichen der Durchschnittstemeperatur von 24° C.: " << time << endl;
	
	return EXIT_SUCCESS;
}
