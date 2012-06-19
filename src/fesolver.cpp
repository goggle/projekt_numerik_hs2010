#include "fesolver.h"

FESolver::FESolver(string tname, string pname, string bname, double zx0, double zy0, double zx1,
	double zy1, double zx2, double zy2, double zx3, double zy3): 
	points(0), edges(0), elements(0), dt(0.2), T_MI(14.0), T_BS(1.3), u(0), img(400, 1000, 2.0, 5.0), cmap(14.0, 28.0)
{
	//elements = vector<Element>();
	//edges = vector<Edge>();
	DataParser::parseData(tname, pname, bname, points, edges, elements);
	size_t npoints = points.size();
	K = SparseMatrix(npoints);
	M = SparseMatrix(npoints);
	l = Vector(npoints);
	
	u = Vector(npoints);
	for (int i = 0; i < (int)npoints; i++) {
		u.setEntry(i, T_MI);
	}

	zx[0] = zx0; zx[1] = zx1; zx[2] = zx2; zx[3] = zx3;
	zy[0] = zy0; zy[1] = zy1; zy[2] = zy2; zy[3] = zy3;

	vector<Element>::iterator it;
	for (it = elements.begin(); it != elements.end(); ++it) {
		ImgTriangle tri(it->getPoint1().getX(), it->getPoint1().getY(), it->getPoint2().getX(), it->getPoint2().getY(),
				it->getPoint3().getX(), it->getPoint3().getY());
		tri.setCoordinates(400, 1000, 2.0, 5.0);
		imgtriangles.push_back(tri);
	}
}

FESolver::~FESolver() {}

void FESolver::assembly() {
	vector<Element>::iterator iter;
	Vertex m; // middle point
	Matrix2 J; // Jacobi matrix
	double detJ; // Determinant of J
	double area; // area of the triangle element
	double fval; // function value
	Matrix3 Kel; // Element stiffness matrix
	Vector lel = Vector(1.0, 1.0, 1.0); // Element load vector
	Matrix3 Mel; // Element mass matrix
	double mel_coeff = 1.0/24.0;


	for (iter = elements.begin(); iter != elements.end(); ++iter) {
		m = iter->getMiddlePoint();
		//J = Matrix2(iter->getPoint1(), iter->getPoint2(), iter->getPoint3());
		J.calculateJacobiMatrix(iter->getPoint1(), iter->getPoint2(), iter->getPoint3());
		detJ = J.det();
		area = 0.5 * abs(detJ);
		Kel.createElementMatrix(area, J);
		Mel.createElementMassMatrix(mel_coeff, detJ);
		fval = fun(m.getX(), m.getY());
		lel.createElementVector(fval, detJ);
		K.addElementMatrix(*iter, Kel);
		M.addElementMatrix(*iter, Mel);
		l.addElementVector(*iter, lel);
	}
		
}

void FESolver::assemblyBoundaryConditions()
{
	vector<Edge>::iterator iter;
	double len;
	Matrix2 M; // Edge Matrix (M1D-el)

	for (iter = edges.begin(); iter != edges.end(); ++iter) {
		if (iter->getLocation() != 0) {
			len = iter->getLength();
			M.getEdgeMatrix(len);
			K.addEdgeMatrix(*iter, M);

			if (iter->getLocation() == 1) { // Edge is a door
				l.addEdgeCondition(*iter, len, T_MI);
			}
			else { // Edge is a window
				l.addEdgeCondition(*iter, len, T_BS);
			}
		}
	}
}


double FESolver::implicitEuler(const char *file)
{
	ofstream stream;
	stream.open(file);

	if (!stream)
		cerr << "Error: Could not open file to write!" << endl;

	double time = 0.0;
	
	K *= dt;
	SparseMatrix A = M + K;
	Vector dtl = l * dt;
	Vector Mu = M * u;
	Vector b = Mu + dtl;
	
	char filename[] = "../movie/plot000.png";
	string name("../movie/plot");
	string type(".png");
	stringstream ss;

	setTriangleColors();
	writeTriangles();
	img.writeImage(filename);

	int iter = 1;

	stream << u << endl;
	string fname;
	while ( u.getMean() <= 24.0 ) {
		ss << name << setfill('0') << setw(3) << iter << type;
		u = A.conjugateGradient(b);

		setTriangleColors();
		writeTriangles();
		img.writeImage(ss.str().c_str());


		time += dt;
		Mu = M * u;
		b = Mu + dtl;
		//cout << u << endl;
		stream << u << endl;

		iter++;
		ss.str("");
	}
	stream.close();
	return time;
}


void FESolver::setTriangleColors()
{
	int n1, n2, n3;
	vector<Element>::iterator it_el;
	vector<ImgTriangle>::iterator it_img;
	for (it_el = elements.begin(), it_img = imgtriangles.begin(); it_el != elements.end(), it_img != imgtriangles.end(); ++it_el, ++it_img) {
		n1 = it_el->getPoint1().getNumber() - 1;	
		n2 = it_el->getPoint2().getNumber() - 1;	
		n3 = it_el->getPoint3().getNumber() - 1;	
		it_img->setP1( cmap.getJetColor(u[n1]) );
		it_img->setP2( cmap.getJetColor(u[n2]) );
		it_img->setP3( cmap.getJetColor(u[n3]) );
	}
}


void FESolver::writeTriangles()
{
	vector<ImgTriangle>::iterator it;
	for (it = imgtriangles.begin(); it != imgtriangles.end(); ++it) {
		img.writeTriangle( *it );
	}

}
