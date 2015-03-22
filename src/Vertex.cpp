//============================================================================
// Name        : Vertex.cpp
// Author      : Zhikai
// Version     :
// Copyright   : (c) 2010 2015 Zhikai Wang/www.heteroclinic.net
// Description : Mock of GTS with limited new features.
//============================================================================
#include "Vertex.h"
/*
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
	Vertex(Point cp, int ci);

	~Vertex();

	int addAnEdge(int e);
	int addATriangle(int t);
};
*/
Vertex::Vertex(Point * cp, int ci, int attr) {
	index = -1;
	attrib = attr;

	vCount= 0;
	vLimit= 5;
int i= 0;
	connectedVertices = new int[vLimit];
	for (i= 0; i<vLimit ; i++)
		connectedVertices[i] = -1;

	eCount= 0;
	eLimit= 5;
	connectedEdges = new int[eLimit];
	for (i= 0; i<eLimit ; i++)
		connectedEdges[i] = -1;

	tCount= 0;
	tLimit= 5;
	connectedTriangles = new int[tLimit];
	for (i= 0; i<tLimit ; i++)
		connectedTriangles[i] = -1;

	index = ci; p.x = cp->x;p.y = cp->y;p.z = cp->z;
}
Vertex::Vertex() {
	index = -1;
	attrib= -1;
int i= 0;
	vCount= 0;
	vLimit= 5;
	connectedVertices = new int[vLimit];
	for (i= 0; i<vLimit ; i++)
		connectedVertices[i] = -1;

	eCount= 0;
	eLimit= 5;
	connectedEdges = new int[eLimit];
	for (i= 0; i<eLimit ; i++)
		connectedEdges[i] = -1;

	tCount= 0;
	tLimit= 5;
	connectedTriangles = new int[tLimit];
	for (i= 0; i<tLimit ; i++)
		connectedTriangles[i] = -1;

}
Vertex::~Vertex() {

	if (connectedVertices!= NULL) {
		delete[] connectedVertices;
		connectedVertices = NULL;
	}

	if (connectedEdges!= NULL) {
		delete[] connectedEdges;
		connectedEdges = NULL;
	}
	if (connectedTriangles!= NULL) {
		delete[] connectedTriangles;
		connectedTriangles = NULL;
	}
}
//	int addAnEdge(int e);ep->
int Vertex::addATriangle(modeltriangle * pgp) {
	addATriangleToList (pgp->index);
	//addAnEdgeToList (pgp->index);
	return 0;
}

int Vertex::addAnEdge (modeledge * ep) {
	if (ep->gp.beg != index && ep->gp.fin != index) {
		printf("Vertex addEdge: Edge not here!");
		exit(0);
	}
	//addAnEdgeToList
	addAnEdgeToList (ep->index);
	//printf("\n%d",ep->index);
	if ( ep->gp.beg == index)
		return addAnVertexToList (ep->gp.fin );
	else 
		return addAnVertexToList (ep->gp.beg );
}

void Vertex::printDetails() {
	printf("\nVertex No. %d ",index);
	int i = 0;
	printf("\nConnected vertices:");
	for (i = 0; i<vCount;i++) {
		printf("%d,",(connectedVertices[i]));
	}
	printf("\nConnected edges:");
	for (i = 0; i<eCount;i++) {
		printf("%d,",(connectedEdges[i]) );
	}
	printf("\nConnected triangles:");
	for (i = 0; i<tCount;i++) {
		printf("%d,",(connectedTriangles[i]) );
	}


	//int * connectedVertices;
	//int vCount;
	//int vLimit;

	//int * connectedEdges;
	//int eCount;
	//int eLimit;

	//int * connectedTriangles;
	//int tCount;
	//int tLimit;

}
int Vertex::addAnVertexToList (int pi) {
	int i = 0;
	int * tmp;
	if (vCount + 1 > vLimit) {
		tmp = new int[vLimit * 2];
		for (i = 0; i<vCount; i++) {
			tmp[i] = connectedVertices[i];
		}
		tmp[i] = pi;
		for (i = vCount+1; i<vLimit * 2; i++)
			//tmp[i] = NULL;
			tmp[i] = -1;
		
		//free(edges);
		//delete [] edges;
		connectedVertices = tmp;
		vLimit = vLimit * 2;
	} else 
		connectedVertices[vCount] = pi;
		//printf("\n");
	//for (i = 0; i<= vCount; i++)
		//printf("%d,",connectedEdges[i]);
	return ++vCount;
}
int Vertex::addATriangleToList (int pi) {
	//int * connectedTriangles;
	//int tCount;
	//int tLimit;
	int i = 0;
	int * tmp;
	if (tCount + 1 > tLimit) {
		tmp = new int[tLimit * 2];
		for (i = 0; i<tCount; i++) {
			tmp[i] = connectedTriangles[i];
		}
		tmp[i] = pi;
		for (i = tCount+1; i<tLimit * 2; i++)
			//tmp[i] = NULL;
			tmp[i] = -1;
		
		//free(edges);
		//delete [] edges;
		connectedTriangles = tmp;
		tLimit = tLimit * 2;
	} else 
		connectedTriangles[tCount] = pi;
	return ++tCount;
}


int Vertex::addAnEdgeToList (int pi) {
	if (index == -1) {
		printf("Add edge to invalid vertex!");
		exit(0);
	}
	int i = 0;
	//for (i = 0; i<edgeCount; i++) {
	//	if (pi  == edges[i])
	//		return edgeCount;
	//}
	int * tmp;
	if (eCount + 1 > eLimit) {
		tmp = new int[eLimit * 2];
		for (i = 0; i<eCount; i++) {
			tmp[i] = connectedEdges[i];
		}
		tmp[i] = pi;
		for (i = eCount+1; i<eLimit * 2; i++)
			//tmp[i] = NULL;
			tmp[i] = -1;
		
		//free(edges);
		//delete [] edges;
		connectedEdges = tmp;
		eLimit = eLimit * 2;
	} else 
		connectedEdges[eCount] = pi;
	return ++eCount;
}
///////////////////////////////////chidao
/*
bool Vertex::haveAnEdges(int ix){

	if (index == -1||edges == NULL || edgeCount <= 0) 
		return false;
	bool existed = false;
	int i = 0;
	for (i = 0; i<edgeCount; i++) {
		if (ix  == edges[i])
			return true;
	}
	return existed;
}

int Vertex::delEdge(int tmpc){
	int count = 0;	int i = 0;
	for (i = 0; i<edgeCount; i++) {
		if (edges[i] == tmpc) 
			count++;
	}
	if (count >0 ) {
		int * tmp;
		tmp = new int [edgeLimit];
		for (int i= 0; i<edgeLimit ; i++)
			tmp[i] = -1;
		int oldcount = edgeCount;
		edgeCount = 0;
		for (i = 0; i< oldcount; i++) {
			if (edges[i] != tmpc && edges[i] != -1 ) {
				tmp[edgeCount++] = edges[i];
			}
		}
		//delete [] edges;
		edges = tmp;
	}
	return count;
}
int Vertex::addEdge (int pi) {
	if (index == -1)
		return 0;
	int i = 0;
	if (pi == index)
		return edgeCount;
	for (i = 0; i<edgeCount; i++) {
		if (pi  == edges[i])
			return edgeCount;
	}
	int * tmp;
	if (edgeCount + 1 > edgeLimit) {
		tmp = new int[edgeLimit * 2];
		for (i = 0; i<edgeCount; i++) {
			tmp[i] = edges[i];
		}
		tmp[i] = pi;
		for (i = edgeCount+1; i<edgeLimit * 2; i++)
			//tmp[i] = NULL;
			tmp[i] = -1;
		
		//free(edges);
		//delete [] edges;
		edges = tmp;
		edgeLimit = edgeLimit * 2;
	} else 
		edges[edgeCount] = pi;
	return ++edgeCount;
}
void Vertex::printEdges() {
	printf("\n Total %d edges: ",edgeCount);
	int i = 0;
	for (i = 0; i<edgeCount; i++)
		printf("%d,",edges[i]);
}
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
