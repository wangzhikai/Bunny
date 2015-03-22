/*
Zhikai Wang

GTS model viewer and primitive simplification tool.
*/
#ifndef __MODEL
#define __MODEL
#include "Vertex.h"
#include "modeledge.h"
#include "modeltriangle.h"
//#include "curvelist.h"
//class modeledge
//class modeltriangle
//#include "basics.h"

class Model;
//void readfile (int file_chosen,Model * mp);
float ptopd ( Point p1, Point p2); 

class Model {
public:
	void offSet();
	float scale1,scale2,scale3;
	void drawNoTransformationSmoothShading();
	void calculateScale();
	float scale;

	int ttlv,ttle,ttlt;
	Vector ** verticesNomals;
	GLfloat * verticesNomalsHeap;
	GLfloat * trianlgesNomalsHeap;
	Vector ** trianlgesNomals;
	Vertex ** vertices;
	modeledge ** edges;
	modeltriangle ** triangles;
	int verticesCount;
	int verticesCountOrigin;
	int verticesLimit;
	int edgesCount;
	int edgesCountOrigin;
	int edgesLimit;
	int trianglesCount;
	int trianglesCountOrigin;
	int trianglesLimit;
	Model ();
	 ~Model();
	int addAVertexToVlist(Point * p, int ci, int attr);
	int addAnEdge(GTSedgePair * pgp,int nindex,int nattrib );
	//modeledge * addAnEdgeToElist(GTSedgePair * pgp,int nindex,int nattrib );
	modeledge * addAnEdgeToElist(_edgePair* pgp,int nindex,int nattrib );


	int addATriangle(GTStriangle * pgp,int nindex,int nattrib );
	modeltriangle * addATriangleToTlist(GTStriangle * pgt,int nindex,int nattrib);
	//int addAnEdgeToElist(GTSedgePair * pgp,int nindex,int nattrib );
	//void initFromCurveList(curvelist * pcl);
	void  drawByVertices();
	void  drawByEdges();
	void  drawByTriangle();
	void	drawByTriangleBK();
	void  drawByTriangle2();// by the avged_norms around a triange
	void  printDetails();
	void initFromFile(char * fn) ;
	void calculateTrianglesNormals();
	void calculateVerticessNormals();
	void drawFlatShading();
	void drawSmoothShading();
	//getAVertex();
	//getAnEdge();
	//getATriangle();
	//checkIntegrity();
	float xmin,xmax,ymin,ymax,zmin,zmax;
	float edgemin, edgemax;
	/*
	int addAVertex (Point p);
	void printVertices ();
	int addAnEdge(int v1, int v2);
	// insertAnEdge(int v1, int v2);
	bool haveAnVertex(int iv);
	void drawByEdge();
	void cluster();
	void decimate();
	int qualifiedVertices( Vertex * pv ,int * qualified_vlist, 
		int * qvcount);
	int rmVertex(int tmpc);
	bool isCandidate( Vertex * vp);
	int countSharedPoint( Vertex * vp1, Vertex * vp2);
	void buildLoop ( Vertex * vp);
	void arrangeSeq ( Vertex * vp1);
	double getTimeElapsed();
	int  addAnEdge (GTSedgePair * pgp);
	*/

	GLfloat OBJ_SIZE;
	//double start_time,end_time;
	int  triangleGetNearTriangles(int tIndex, int * & arr );
	void  giveTheNormOfATriangle(int index,Vector & Norm );
	void  giveTheAvgNormOfATriangle(int tIndex,Vector & Norm );

};
#endif
/* bk in July 3
class Model {
public:
	GLfloat OBJ_SIZE;
	double start_time,end_time;
	int ttlv,ttle,ttlt;
	Vertex ** vertices;
	modeledge ** edges;
	modeltriangle ** triangles;

	int verticesCount;
	int verticesCountOrigin;
	int verticesLimit;

	int edgesCount;
	int edgesCountOrigin;
	int edgesLimit;

	int trianglesCount;
	int trianglesCountOrigin;
	int trianglesLimit;

	GLfloat xmin,xmax,ymin,ymax,zmin,zmax;
	GLfloat edgemin, edgemax;
	Model ();
	 ~Model();
	int addAVertex (Point p);
	void printVertices ();
	int addAnEdge(int v1, int v2);
	// insertAnEdge(int v1, int v2);
	bool haveAnVertex(int iv);
	void drawByEdge();
	void cluster();
	void decimate();
	int qualifiedVertices( Vertex * pv ,int * qualified_vlist, 
		int * qvcount);
	int rmVertex(int tmpc);
	bool isCandidate( Vertex * vp);
	int countSharedPoint( Vertex * vp1, Vertex * vp2);
	void buildLoop ( Vertex * vp);
	void arrangeSeq ( Vertex * vp1);
	double getTimeElapsed();
	int  addAnEdge (GTSedgePair * pgp);
};
*/
/*
int main () {
	Model m;
	Point p ; p.x = 1; p.y =4; p.z = 7;
	//v = new Vertex(p,3);
	//printf("\nConstructed");
	int i = 0;
	int tmp = 0;
	for (i = 0; i<5; i++) {
		m.addAVertex(p);
	}
	//addAnEdge(int v1, int v2)
	int tmp2 = 0;
	for (i = 0; i<20; i++) {
		tmp = rand() % 5;
		tmp2 = rand() % 5;
		printf("\nAdd edge %d  , %d ",tmp,tmp2);
		m.addAnEdge(tmp,tmp2);
		//m.addAVertex(p);
	}
	m.printVertices();


	return 0;
}
*/
/*
int addEdge (int pi) {
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
		for (i = 0; i<edgeCount; i++)
			tmp[i] = edges[i];
		tmp[i] = pi;
		free(edges);
		edges = tmp;
		edgeLimit = edgeLimit * 2;
	} else 
		edges[edgeCount] = pi;
	return edgeCount++;
}
*/

/*
// test vertices
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
