#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "vertex.h"
#include "edge.h"
#include "element.h"

using namespace std;

class DataParser{
	private:

	public:
		static int countLines(string filename);
		static void parseData(string tfname, string pfname, string bfname,
			vector<Vertex> &points, vector<Edge> &edges, vector<Element> &el);

};

#endif // DATAPARSER_H
