#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "dataparser.h"
#include "vertex.h"
#include "edge.h"
#include "element.h"


using namespace std;

int main()
{
	string tname("t_grob.dat");
	string pname("p_grob.dat");
	string bname("b_grob.dat");
	vector<Vertex> points;
	vector<Edge> edges;
	vector<Element> elements;
	DataParser::parseData(tname, pname, bname, points, edges, elements);
	
	ofstream file;
	file.open("plot_grob.dat");
	if (!file) {
		cerr << "Error: Could not open file to write!" << endl;
		return EXIT_FAILURE;
	}

	vector<Edge>::iterator iter;
	for (iter = edges.begin(); iter != edges.end(); ++iter) {
		file 	<< setw(20)
					<< iter->getPoint1().getX()
					<< setw(20)
					<< iter->getPoint1().getY()
					<< setw(20)
					<< iter->getPoint2().getX()
					<< setw(20)
					<< iter->getPoint2().getY()
					<< setw(20)
					<< iter->getLocation()
					<< endl;
	}

	file.close();
	
	return EXIT_SUCCESS;
}
