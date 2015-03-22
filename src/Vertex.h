#ifndef __VERTEX
#define __VERTEX
#include "basics.h"
#include "modeledge.h"
#include "modeltriangle.h"
class Vertex {
public:
	Point p;
	int index;
	int attrib;

	int * connectedVertices;
	int vCount;
	int vLimit;

	int * connectedEdges;
	int eCount;
	int eLimit;

	int * connectedTriangles;
	int tCount;
	int tLimit;

	Vertex();
	//Vertex(Point cp, int ci);
	 Vertex(Point * cp, int ci, int attr);

	~Vertex();

	//int addAnEdge(int e);
	//int addATriangle(int t);
	int addAnEdgeToList (int pi);
	///?????
	//int addAnEdge (GTSedgePair * ep);
	//int addAnEdge (const GTSedgePair & ep);

	int  addAnEdge (modeledge * ep) ;
	int addAnVertexToList (int pi);
	//int  addAnEdge (modeledge * ep) ;
	int  addATriangle(modeltriangle * pgp);
	int  addATriangleToList (int pi);
	void  printDetails();
};
#endif
/*
//backup July 3,07
class Vertex {
public:
	Point p;
	int edgeCount;
	int edgeLimit;
	int index;
	int attrib;
	int * edges;
	Vertex();
	~Vertex();
	Vertex(Point cp, int ci);
	int delEdge(int tmpc);
	int addEdge (int pi);
	void printEdges();
	bool haveAnEdges(int ix);
};
*/
/* to test vertex
int main () {
	Vertex * v;
	Point p ; p.x = 1; p.y =4; p.z = 7;
	v = new Vertex(p,3);
	printf("\nConstructed");
	int i = 0;
	int tmp = 0;
	for (i = 0; i<100; i++) {
		tmp = rand() % 15;
		v->insertEdge(tmp);
		v->printEdges();
		printf(" ; inser %d ",tmp);
	}


	return 0;
}
*/
