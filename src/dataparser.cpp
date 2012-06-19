#include "dataparser.h"

/*
 Count the lines in the specified file
*/
int DataParser::countLines(string filename)
{
	ifstream file;
	file.open(filename.c_str());
	if (!file) {
		cerr << "Could not open data file..." << endl;
	}
	
	int count = 0;
	string line;
	while (getline(file, line)) {
		count++;
	}

	return count;
} 


void DataParser::parseData(string tfname, string pfname, string bfname,
	vector<Vertex> &points, vector<Edge> &edges, vector<Element> &triangles)
{
	string line;
	int *t1, *t2, *t3, *b1, *b2, *b3;
	double *p1, *p2;
	int ntlines, nplines, nblines;

	string dataDir("../data/");
	ifstream file;	

	tfname = dataDir + tfname;
	pfname = dataDir + pfname;
	bfname = dataDir + bfname;

	ntlines = countLines(tfname);
	nplines = countLines(pfname);
	nblines = countLines(bfname);

	t1 = new int[ntlines];
	t2 = new int[ntlines];
	t3 = new int[ntlines];
	b1 = new int[nblines];
	b2 = new int[nblines];
	b3 = new int[nblines];
	p1 = new double[nplines];
	p2 = new double[nplines];

	// Process the file containing the triangles:
	file.open(tfname.c_str());
	if (!file) {
		cerr << "Could not open data file. (1)" << endl;
	}
	int c = 0;
	double val;
	// Read the triangle file:
	while (getline(file, line)) {
		istringstream stream(line);
		//while (stream >> val) {
			//cout << " " << d <<  endl;
		//}
		stream >> val;
		t1[c] = val;
		stream >> val;
		t2[c] = val;
		stream >> val;
		t3[c] = val;
		c++;
	}
	c = 0;
	file.close();

	// Process the file containing the point data:
	file.open(pfname.c_str());
	if (!file) {
		cerr << "Could not open data file. (2)" << endl;
	}
	while (getline(file, line)) {
		istringstream stream(line);
		stream >> val;
		p1[c] = val;
		stream >> val;
		p2[c] = val;
		c++;
	}
	c = 0;
	file.close();

	// Process the file containing the edge data:
	file.open(bfname.c_str());
	if (!file) {
		cerr << "Could not open data file. (3)" << endl;
	}
	while (getline(file, line)) {
		istringstream stream(line);
		stream >> val;
		b1[c] = val;
		stream >> val;
		b2[c] = val;
		stream >> val;
		b3[c] = val;
		c++;
	}
	c = 0;
	file.close();

	for (int i = 0; i < nplines; i++) {
		points.push_back(Vertex(i+1, p1[i], p2[i])); // BEWARE: The first Vertex has number 1, not 0!
	}

	// TODO: process column 2 and 3...
	for (int i = 0; i < nblines; i++) {
		//vertex[b1[i]-1].setLocation(1);
		points[b1[i]-1].setLocation(b3[i]);
		points[b2[i]-1].setLocation(b3[i]);
	}

	// Create the edges:
	for (int i = 0; i < nblines; i++) {
		Edge edge(points[b1[i] - 1], points[b2[i] - 1], b3[i]);
		edges.push_back(edge);
	}
	
	//for (int i = 0; i < nplines; i++) {
	//	cout << vertex[i].getNumber() << ", x = " << vertex[i].getX() << ", y = " << vertex[i].getY() << ", " << vertex[i].getLocation() << endl;
	//}

	//vector<Element> triangles;
	for (int i = 0; i < ntlines; i++) {
		Element elem(points[t1[i] - 1], points[t2[i] - 1], points[t3[i] - 1]);
		triangles.push_back(elem);
	}


//	for (int i = 0; i < nplines; i++) {
//		cout << points[i] << endl;
//	}
//	for (int i = 0; i < ntlines; i++) {
//		cout << triangles[i] << endl;
//	}
//	for (int i = 0; i < nblines; i++) {
//		cout << edges[i] << endl;
//	}

	delete[] t1;
	delete[] t2;
	delete[] t3;
	delete[] b1;
	delete[] b2;
	delete[] b3;
	delete[] p1;
	delete[] p2;

}
