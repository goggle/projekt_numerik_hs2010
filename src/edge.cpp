#include "edge.h"

Edge::Edge(): point1(NULL), point2(NULL), loc(-1)  {}
Edge::Edge(Vertex &v1, Vertex &v2): point1(&v1), point2(&v2), loc(-1) {}
Edge::Edge(Vertex &v1, Vertex &v2, int l): point1(&v1), point2(&v2), loc(l) {}
