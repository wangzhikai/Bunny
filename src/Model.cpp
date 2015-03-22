#include "model.h"
/*
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
Model ();
Model::~Model();
int addAVertexToVlist(const Point & p, int ci, int attr);
int addAnEdge(GTSedgePair * pgp,int nindex,int nattrib );
int addAnEdgeToElist(GTSedgePair * pgp,int nindex,int nattrib );
int addATriangleToTlist(GTStriangle * pgt,int nindex,int nattrib);
void initFromCurveList();

//getAVertex();
//getAnEdge();
//getATriangle();
//checkIntegrity();

GLfloat xmin,xmax,ymin,ymax,zmin,zmax;
GLfloat edgemin, edgemax;
//GLfloat OBJ_SIZE;
//double start_time,end_time;
*/
/*
vc1.x = v2.x - v1.x;
vc1.y = v2.y - v1.y;
vc1.z = v2.z - v1.z;
vc2.x = v3.x - v1.x;
vc2.y = v3.y - v1.y;
vc2.z = v3.z - v1.z;
crossVector(&vc2,&vc1,&Norm);
glNormal3f(Norm.x,Norm.y,Norm.z);
*/
//	Point v1,v2,v3;
//	Vector vc1,vc2,Norm;

//Vector ** verticesNomals;
//Vector ** trianlgesNomals;
//void Model::calculateTrianglesNormals()
//{
//
//
//	for (int i = 0; i< trianglesCount; i++ ) {
//		pt = triangles[i];
//
//		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
//			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
//				iv1 =  edges[pt->gt.e1-1]->gp.beg;
//				iv2 =  edges[pt->gt.e1-1]->gp.fin;
//		} else {
//			iv1 =  edges[pt->gt.e1-1]->gp.fin;
//			iv2 =  edges[pt->gt.e1-1]->gp.beg;
//		}
//		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
//			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
//				iv3 =  edges[pt->gt.e2-1]->gp.beg;
//		} else {
//			iv3 =  edges[pt->gt.e2-1]->gp.fin;
//		}
//		v1.x = vertices[iv1-1]->p.x;
//		v1.y = vertices[iv1-1]->p.y;
//		v1.z = vertices[iv1-1]->p.z;
//		v2.x = vertices[iv2-1]->p.x;
//		v2.y = vertices[iv2-1]->p.y;
//		v2.z = vertices[iv2-1]->p.z;
//		v3.x = vertices[iv3-1]->p.x;
//		v3.y = vertices[iv3-1]->p.y;
//		v3.z = vertices[iv3-1]->p.z;
//
//	
//
//		vc1.x = v1.x - v2.x;
//		vc1.y = v1.y - v2.y;
//		vc1.z = v1.z - v2.z;
//		vc2.x = v1.x - v3.x;
//		vc2.y = v1.y - v3.y;
//		vc2.z = v1.z - v3.z;
//		//float t = crossVector(&vc2,&vc1,&Norm);
//		float t = crossVector(&vc1,&vc2,&Norm);
//
//		glBegin(GL_TRIANGLES);
//		glNormal3f(Norm.x/t,Norm.y/t,Norm.z/t);
//		glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z);
//		glEnd();			
//	}
//
//	glPopMatrix();
//}	
void Model::offSet() {
	//scale1 = OBJ_SIZE/(xmax - xmin);
	//scale2 = OBJ_SIZE/(ymax - ymin);
	//scale3 = OBJ_SIZE/(zmax - zmin);
	//float scale = 
	//	(
	//	((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
	//	?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
	//	)
	//	?
	//	((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
	//	?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	//glPushMatrix();
	//glScalef(scale,scale,scale);
	//glScalef(1.0,1.0,1.0);
	//glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	float tmpxmin = xmin,tmpymin = ymin,tmpzmin = zmin;
	float tmpxmax = xmax,tmpymax = ymax,tmpzmax = zmax;

	tmpxmin *= scale;	tmpymin *= scale;	tmpzmin *= scale;
	tmpxmax *= scale;	tmpymax *= scale;	tmpzmax *= scale;
	printf("\nscale:%f\n",scale);
	float offsetx = (tmpxmin + tmpxmax)/2.0;
	float offsety = (tmpymin + tmpymax)/2.0;
	float offsetz = (tmpzmin + tmpzmax)/2.0;
	xmin = tmpxmin - offsetx;
	xmax = tmpxmax - offsetx;
	ymin = tmpymin - offsety;
	ymax = tmpymax - offsety;
	zmin = tmpzmin - offsetz;
	zmax = tmpzmax - offsetz;


	edgemin *= scale, edgemax*= scale;
	int i = 0;
//vertices[iv1-1]->p.
	for ( i = 0; i<verticesCount;i++) {
			vertices[i]->p.x *= scale;
			vertices[i]->p.x -= offsetx;
			vertices[i]->p.y *= scale;
			vertices[i]->p.y -= offsety;
			vertices[i]->p.z *= scale;
			vertices[i]->p.z -= offsetz;
	}


}
void Model::calculateScale() {
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	//glPushMatrix();
	//glScalef(scale,scale,scale);
	//glScalef(1.0,1.0,1.0);
	//glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);

}
void Model::drawNoTransformationSmoothShading() {
	printf("\n draw bunny smooth shading");

	int tmp = 0;
	Point v1,v2,v3;
	Vector vc1,vc2,Norm;


	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	int ivbk1=-1,ivbk2=-1,ivbk3=-1;
	//bool stripHead= true;
	int flipcount =  0;
	//printf("\n %d triangle count",trianglesCount);
	glDisable(GL_CULL_FACE);
	for (int i = 0; i< trianglesCount; i++ ) {
		pt = triangles[i];

		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e1-1]->gp.fin;
		} else {
			iv1 =  edges[pt->gt.e1-1]->gp.fin;
			iv2 =  edges[pt->gt.e1-1]->gp.beg;

		}

		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
				iv3 =  edges[pt->gt.e2-1]->gp.beg;
		} else {
			iv3 =  edges[pt->gt.e2-1]->gp.fin;
		}
		glBegin(GL_TRIANGLES);
		//glNormal3f(Norm.x*scale,Norm.y*scale,Norm.z*scale);
		//glScalef(scale,scale,scale);
		//glNormal3f((trianlgesNomals[i])->x*scale,(trianlgesNomals[i])->y*scale,(trianlgesNomals[i])->z*scale);
	//	//glNormal3fv((GLfloat *)trianlgesNomals[i]);
		//glNormal3f((verticesNomals[iv1-1])->x*scale,(verticesNomals[iv1-1])->y*scale,(verticesNomals[iv1-1])->z*scale);
		//glVertex3fv((GLfloat *)&vertices[iv1-1]->p);
		//glNormal3f((verticesNomals[iv2-1])->x*scale,(verticesNomals[iv2-1])->y*scale,(verticesNomals[iv2-1])->z*scale);
		//glVertex3fv((GLfloat *)&vertices[iv2-1]->p);
		//glNormal3f((verticesNomals[iv3-1])->x*scale,(verticesNomals[iv3-1])->y*scale,(verticesNomals[iv3-1])->z*scale);
		//glVertex3fv((GLfloat *)&vertices[iv3-1]->p);
		glNormal3f((verticesNomals[iv1-1])->x,(verticesNomals[iv1-1])->y,(verticesNomals[iv1-1])->z);
		glVertex3fv((GLfloat *)&vertices[iv1-1]->p);
		glNormal3f((verticesNomals[iv2-1])->x,(verticesNomals[iv2-1])->y,(verticesNomals[iv2-1])->z);
		glVertex3fv((GLfloat *)&vertices[iv2-1]->p);
		glNormal3f((verticesNomals[iv3-1])->x,(verticesNomals[iv3-1])->y,(verticesNomals[iv3-1])->z);
		glVertex3fv((GLfloat *)&vertices[iv3-1]->p);

		glEnd();			
	}

//	glPopMatrix();
}


void Model::drawSmoothShading() {
	printf("\n draw bunny smooth shading");

	float scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	float scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	//glScalef(1.0,1.0,1.0);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	int tmp = 0;
	Point v1,v2,v3;
	Vector vc1,vc2,Norm;


	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	int ivbk1=-1,ivbk2=-1,ivbk3=-1;
	//bool stripHead= true;
	int flipcount =  0;
	//printf("\n %d triangle count",trianglesCount);
	glDisable(GL_CULL_FACE);
	for (int i = 0; i< trianglesCount; i++ ) {
		pt = triangles[i];

		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e1-1]->gp.fin;
		} else {
			iv1 =  edges[pt->gt.e1-1]->gp.fin;
			iv2 =  edges[pt->gt.e1-1]->gp.beg;

		}

		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
				iv3 =  edges[pt->gt.e2-1]->gp.beg;
		} else {
			iv3 =  edges[pt->gt.e2-1]->gp.fin;
		}



		glBegin(GL_TRIANGLES);
		//glNormal3f(Norm.x*scale,Norm.y*scale,Norm.z*scale);
		//glScalef(scale,scale,scale);
		//glNormal3f((trianlgesNomals[i])->x*scale,(trianlgesNomals[i])->y*scale,(trianlgesNomals[i])->z*scale);
	//	//glNormal3fv((GLfloat *)trianlgesNomals[i]);
		glNormal3f((verticesNomals[iv1-1])->x*scale,(verticesNomals[iv1-1])->y*scale,(verticesNomals[iv1-1])->z*scale);
		glVertex3fv((GLfloat *)&vertices[iv1-1]->p);
		glNormal3f((verticesNomals[iv2-1])->x*scale,(verticesNomals[iv2-1])->y*scale,(verticesNomals[iv2-1])->z*scale);
		glVertex3fv((GLfloat *)&vertices[iv2-1]->p);
		glNormal3f((verticesNomals[iv3-1])->x*scale,(verticesNomals[iv3-1])->y*scale,(verticesNomals[iv3-1])->z*scale);
		glVertex3fv((GLfloat *)&vertices[iv3-1]->p);
		glEnd();			
	}

	glPopMatrix();
}

void Model::drawFlatShading() {

	float scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	float scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	//glScalef(1.0,1.0,1.0);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	int tmp = 0;
	Point v1,v2,v3;
	Vector vc1,vc2,Norm;


	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	int ivbk1=-1,ivbk2=-1,ivbk3=-1;
	//bool stripHead= true;
	int flipcount =  0;
	//printf("\n %d triangle count",trianglesCount);
	glDisable(GL_CULL_FACE);
	for (int i = 0; i< trianglesCount; i++ ) {
		pt = triangles[i];
		//  if ( (edges[0]->vertices[0] != edges[1]->vertices[0]) &&
		//     (edges[0]->vertices[0] != edges[1]->vertices[1]) )
		//{
		//    vertices[0]=edges[0]->vertices[0];
		//    vertices[1]=edges[0]->vertices[1];
		//}
		//else
		//{
		//    vertices[0]=edges[0]->vertices[1];
		//    vertices[1]=edges[0]->vertices[0];
		//}

		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e1-1]->gp.fin;
		} else {
			iv1 =  edges[pt->gt.e1-1]->gp.fin;
			iv2 =  edges[pt->gt.e1-1]->gp.beg;

		}

		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
				iv3 =  edges[pt->gt.e2-1]->gp.beg;
		} else {
			iv3 =  edges[pt->gt.e2-1]->gp.fin;
		}



		glBegin(GL_TRIANGLES);
		//glNormal3f(Norm.x*scale,Norm.y*scale,Norm.z*scale);
		//glScalef(scale,scale,scale);
		glNormal3f((trianlgesNomals[i])->x*scale,(trianlgesNomals[i])->y*scale,(trianlgesNomals[i])->z*scale);
	//	//glNormal3fv((GLfloat *)trianlgesNomals[i]);
		glVertex3fv((float *)&vertices[iv1-1]->p);
		glVertex3fv((float *)&vertices[iv2-1]->p);
		glVertex3fv((float *)&vertices[iv3-1]->p);
		glEnd();			
	}

	glPopMatrix();


	//GLfloat scale1,scale2,scale3;
	//scale1 = OBJ_SIZE/(xmax - xmin);
	//scale2 = OBJ_SIZE/(ymax - ymin);
	//scale3 = OBJ_SIZE/(zmax - zmin);
	//GLfloat scale = 
	//	(
	//	((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
	//	?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
	//	)
	//	?
	//	((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
	//	?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	//glPushMatrix();
	//glScalef(scale,scale,scale);
	//glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	//Point v1,v2,v3;
	//Vector vc1,vc2,Norm;
	//	int iv1=-1,iv2=-1,iv3=-1;

	//modeltriangle * pt;
	//for (int i = 0; i< trianglesCount; i++ ) {
	//	pt = triangles[i];

	//	if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
	//		&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
	//			iv1 =  edges[pt->gt.e1-1]->gp.beg;
	//			iv2 =  edges[pt->gt.e1-1]->gp.fin;
	//	} else {
	//		iv1 =  edges[pt->gt.e1-1]->gp.fin;
	//		iv2 =  edges[pt->gt.e1-1]->gp.beg;

	//	}

	//	if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
	//		&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
	//			iv3 =  edges[pt->gt.e2-1]->gp.beg;
	//	} else {
	//		iv3 =  edges[pt->gt.e2-1]->gp.fin;
	//	}

	//	v1.x = vertices[iv1-1]->p.x;
	//	v1.y = vertices[iv1-1]->p.y;
	//	v1.z = vertices[iv1-1]->p.z;
	//	v2.x = vertices[iv2-1]->p.x;
	//	v2.y = vertices[iv2-1]->p.y;
	//	v2.z = vertices[iv2-1]->p.z;
	//	v3.x = vertices[iv3-1]->p.x;
	//	v3.y = vertices[iv3-1]->p.y;
	//	v3.z = vertices[iv3-1]->p.z;

	//	vc1.x = v1.x - v2.x;
	//	vc1.y = v1.y - v2.y;
	//	vc1.z = v1.z - v2.z;
	//	vc2.x = v1.x - v3.x;
	//	vc2.y = v1.y - v3.y;
	//	vc2.z = v1.z - v3.z;
	//	//float t = crossVector(&vc2,&vc1,&Norm);
	//	float t = crossVector(&vc1,&vc2,&Norm);
	//	trianlgesNomals[i]->x = Norm.x;
	//	trianlgesNomals[i]->y = Norm.y;
	//	trianlgesNomals[i]->z = Norm.z;
	//	glNormal3f(Norm.x,Norm.y,Norm.z);
	//	glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z);
	//	//glNormal3fv((GLfloat *)trianlgesNomals[i]);
	//	//glVertex3fv((GLfloat *)&vertices[iv1-1]->p);
	//	//glVertex3fv((GLfloat *)&vertices[iv2-1]->p);
	//	//glVertex3fv((GLfloat *)&vertices[iv3-1]->p);
	//}
	//	glPopMatrix();
}



//void Model::drawFlatShading() {
//
//	GLfloat scale1,scale2,scale3;
//	scale1 = OBJ_SIZE/(xmax - xmin);
//	scale2 = OBJ_SIZE/(ymax - ymin);
//	scale3 = OBJ_SIZE/(zmax - zmin);
//	GLfloat scale = 
//		(
//		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
//		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
//		)
//		?
//		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
//		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
//	glPushMatrix();
//	//glScalef(scale,scale,scale);
//	glScalef(1.0,1.0,1.0);
//	glTranslatef(-(xmin*scale+xmax*scale)/2,-(ymin*scale+ymax*scale)/2,-(zmin*scale+zmax*scale)/2);
//	int tmp = 0;
//	Point v1,v2,v3;
//	Vector vc1,vc2,Norm;
//
//
//	modeltriangle * pt;
//	int iv1=-1,iv2=-1,iv3=-1;
//	int ivbk1=-1,ivbk2=-1,ivbk3=-1;
//	//bool stripHead= true;
//	int flipcount =  0;
//	//printf("\n %d triangle count",trianglesCount);
//	glDisable(GL_CULL_FACE);
//	for (int i = 0; i< trianglesCount; i++ ) {
//		pt = triangles[i];
//		//  if ( (edges[0]->vertices[0] != edges[1]->vertices[0]) &&
//		//     (edges[0]->vertices[0] != edges[1]->vertices[1]) )
//		//{
//		//    vertices[0]=edges[0]->vertices[0];
//		//    vertices[1]=edges[0]->vertices[1];
//		//}
//		//else
//		//{
//		//    vertices[0]=edges[0]->vertices[1];
//		//    vertices[1]=edges[0]->vertices[0];
//		//}
//
//		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
//			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
//				iv1 =  edges[pt->gt.e1-1]->gp.beg;
//				iv2 =  edges[pt->gt.e1-1]->gp.fin;
//		} else {
//			iv1 =  edges[pt->gt.e1-1]->gp.fin;
//			iv2 =  edges[pt->gt.e1-1]->gp.beg;
//
//		}
//
//		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
//			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
//				iv3 =  edges[pt->gt.e2-1]->gp.beg;
//		} else {
//			iv3 =  edges[pt->gt.e2-1]->gp.fin;
//		}
//
//
//		//if ( (edges[1]->vertices[0] != edges[0]->vertices[0]) &&
//		//     (edges[1]->vertices[0] != edges[0]->vertices[1]) )
//		//{
//		//    vertices[2]=edges[1]->vertices[0];
//		//}
//		//else
//		//{
//		//    vertices[2]=edges[1]->vertices[1];
//		//}
//
//		/*		if ( edges[pt->gt.e1-1]->gp.beg
//		!= edges[pt->gt.e2-1]->gp.beg  ) {
//		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin) {
//
//		iv1 =  edges[pt->gt.e1-1]->gp.beg;
//		iv2 =  edges[pt->gt.e1-1]->gp.fin;
//		iv3 =  edges[pt->gt.e1-1]->gp.fin;
//		}
//		}
//		else {
//		if ( edges[pt->gt.e1-1]->gp.beg 
//		== edges[pt->gt.e2-1]->gp.fin) {
//		iv1 = edges[pt->gt.e1-1]->gp.beg;
//		iv2 =  edges[pt->gt.e2-1]->gp.beg;
//		iv3 =  edges[pt->gt.e1-1]->gp.fin;
//		}
//		else {
//		iv1 = edges[pt->gt.e1-1]->gp.fin;
//		iv2 =  edges[pt->gt.e2-1]->gp.beg;
//		iv3 =  edges[pt->gt.e1-1]->gp.beg;
//		}
//		}*/
//
//
//		//if ( edges[pt->gt.e1-1]->gp.beg
//		//	=edges[pt->gt.e2-1]->gp.beg  ) {
//		//	iv1 =  edges[pt->gt.e1-1]->gp.beg;
//		//	iv2 =  edges[pt->gt.e2-1]->gp.fin;
//		//	iv3 =  edges[pt->gt.e1-1]->gp.fin;
//		//}
//		//else {
//		//	if ( edges[pt->gt.e1-1]->gp.beg 
//		//		== edges[pt->gt.e2-1]->gp.fin) {
//		//		iv1 = edges[pt->gt.e1-1]->gp.beg;
//		//		iv2 =  edges[pt->gt.e2-1]->gp.beg;
//		//		iv3 =  edges[pt->gt.e1-1]->gp.fin;
//		//	}
//		//	else {
//		//		iv1 = edges[pt->gt.e1-1]->gp.fin;
//		//		iv2 =  edges[pt->gt.e2-1]->gp.beg;
//		//		iv3 =  edges[pt->gt.e1-1]->gp.beg;
//		//	}
//		//}
//		v1.x = vertices[iv1-1]->p.x;
//		v1.y = vertices[iv1-1]->p.y;
//		v1.z = vertices[iv1-1]->p.z;
//		v2.x = vertices[iv2-1]->p.x;
//		v2.y = vertices[iv2-1]->p.y;
//		v2.z = vertices[iv2-1]->p.z;
//		v3.x = vertices[iv3-1]->p.x;
//		v3.y = vertices[iv3-1]->p.y;
//		v3.z = vertices[iv3-1]->p.z;
//
//		//vc1.x = v2.x - v1.x;
//		//vc1.y = v2.y - v1.y;
//		//vc1.z = v2.z - v1.z;
//		//vc2.x = v3.x - v1.x;
//		//vc2.y = v3.y - v1.y;
//		//vc2.z = v3.z - v1.z;
//
//		vc1.x = v1.x - v2.x;
//		vc1.y = v1.y - v2.y;
//		vc1.z = v1.z - v2.z;
//		vc2.x = v1.x - v3.x;
//		vc2.y = v1.y - v3.y;
//		vc2.z = v1.z - v3.z;
//		//float t = crossVector(&vc2,&vc1,&Norm);
//		float t = crossVector(&vc1,&vc2,&Norm);
//		//float t = sqrt(Norm.x*Norm.x + Norm.y*Norm.y+ Norm.z*Norm.z);
//		//if (t>0)
//		//if ( iv1 == ivbk1 || iv1 == ivbk2 || iv1 == ivbk3 ||
//		//	iv2 == ivbk1 || iv2 == ivbk2 || iv2 == ivbk3 ||
//		//	iv3 == ivbk1 || iv3 == ivbk2 || iv3 == ivbk3)
//		//	flipcount++;
//		//else
//		//	flipcount = 0;
//
//		glBegin(GL_TRIANGLES);
//		glNormal3f(Norm.x,Norm.y,Norm.z);
//		//glScalef(scale,scale,scale);
//		//glNormal3f((trianlgesNomals[i])->x/scale,(trianlgesNomals[i])->y/scale,(trianlgesNomals[i])->z/scale);
//		//glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z);
//		glVertex3f(v1.x*scale,v1.y*scale,v1.z*scale);glVertex3f(v2.x*scale,v2.y*scale,v2.z*scale);glVertex3f(v3.x*scale,v3.y*scale,v3.z*scale);
//		//if (flipcount %2 == 0) {
//		//	 glNormal3f(Norm.x/t,Norm.y/t,Norm.z/t);
//		//	glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z); 
//		//}
//		//else {
//		//		glNormal3f(-Norm.x/t,-Norm.y/t,-Norm.z/t);
//		//		glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v3.x,v3.y,v3.z);
//		//		printf("\n%d inverse triangle",i);
//		//}
//		glEnd();			
//		//ivbk1=iv1,ivbk2=iv2,ivbk3=iv3;
//	}
//
//	glPopMatrix();
//
//
//	//GLfloat scale1,scale2,scale3;
//	//scale1 = OBJ_SIZE/(xmax - xmin);
//	//scale2 = OBJ_SIZE/(ymax - ymin);
//	//scale3 = OBJ_SIZE/(zmax - zmin);
//	//GLfloat scale = 
//	//	(
//	//	((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
//	//	?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
//	//	)
//	//	?
//	//	((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
//	//	?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
//	//glPushMatrix();
//	//glScalef(scale,scale,scale);
//	//glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
//	//Point v1,v2,v3;
//	//Vector vc1,vc2,Norm;
//	//	int iv1=-1,iv2=-1,iv3=-1;
//
//	//modeltriangle * pt;
//	//for (int i = 0; i< trianglesCount; i++ ) {
//	//	pt = triangles[i];
//
//	//	if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
//	//		&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
//	//			iv1 =  edges[pt->gt.e1-1]->gp.beg;
//	//			iv2 =  edges[pt->gt.e1-1]->gp.fin;
//	//	} else {
//	//		iv1 =  edges[pt->gt.e1-1]->gp.fin;
//	//		iv2 =  edges[pt->gt.e1-1]->gp.beg;
//
//	//	}
//
//	//	if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
//	//		&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
//	//			iv3 =  edges[pt->gt.e2-1]->gp.beg;
//	//	} else {
//	//		iv3 =  edges[pt->gt.e2-1]->gp.fin;
//	//	}
//
//	//	v1.x = vertices[iv1-1]->p.x;
//	//	v1.y = vertices[iv1-1]->p.y;
//	//	v1.z = vertices[iv1-1]->p.z;
//	//	v2.x = vertices[iv2-1]->p.x;
//	//	v2.y = vertices[iv2-1]->p.y;
//	//	v2.z = vertices[iv2-1]->p.z;
//	//	v3.x = vertices[iv3-1]->p.x;
//	//	v3.y = vertices[iv3-1]->p.y;
//	//	v3.z = vertices[iv3-1]->p.z;
//
//	//	vc1.x = v1.x - v2.x;
//	//	vc1.y = v1.y - v2.y;
//	//	vc1.z = v1.z - v2.z;
//	//	vc2.x = v1.x - v3.x;
//	//	vc2.y = v1.y - v3.y;
//	//	vc2.z = v1.z - v3.z;
//	//	//float t = crossVector(&vc2,&vc1,&Norm);
//	//	float t = crossVector(&vc1,&vc2,&Norm);
//	//	trianlgesNomals[i]->x = Norm.x;
//	//	trianlgesNomals[i]->y = Norm.y;
//	//	trianlgesNomals[i]->z = Norm.z;
//	//	glNormal3f(Norm.x,Norm.y,Norm.z);
//	//	glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z);
//	//	//glNormal3fv((GLfloat *)trianlgesNomals[i]);
//	//	//glVertex3fv((GLfloat *)&vertices[iv1-1]->p);
//	//	//glVertex3fv((GLfloat *)&vertices[iv2-1]->p);
//	//	//glVertex3fv((GLfloat *)&vertices[iv3-1]->p);
//	//}
//	//	glPopMatrix();
//}
void Model::calculateTrianglesNormals() 
{

	int tmp = 0;
	Point v1,v2,v3;
	Vector vc1,vc2,Norm;
	trianlgesNomals = (Vector **) malloc( trianglesCount* sizeof( Vector *));
	verticesNomals = (Vector **) malloc( verticesCount* sizeof( Vector *));
	//GLfloat * verticesNomalsHeap;
	//trianlgesNomalsHeap = (GLfloat *)malloc( trianglesCount* sizeof( Vector ));
	int i=0;
	float t = 1.0;
	for ( i = 0; i<verticesCount;i++) {
		verticesNomals[i] = new Vector;
		verticesNomals[i]->x =0.0;
		verticesNomals[i]->y =0.0;
		verticesNomals[i]->z =0.0;
	}

	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	for (i = 0; i< trianglesCount; i++ ) {
		trianlgesNomals[i] = new Vector;
		pt = triangles[i];

		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e1-1]->gp.fin;
		} else {
			iv1 =  edges[pt->gt.e1-1]->gp.fin;
			iv2 =  edges[pt->gt.e1-1]->gp.beg;

		}

		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
				iv3 =  edges[pt->gt.e2-1]->gp.beg;
		} else {
			iv3 =  edges[pt->gt.e2-1]->gp.fin;
		}

		v1.x = vertices[iv1-1]->p.x;
		v1.y = vertices[iv1-1]->p.y;
		v1.z = vertices[iv1-1]->p.z;
		v2.x = vertices[iv2-1]->p.x;
		v2.y = vertices[iv2-1]->p.y;
		v2.z = vertices[iv2-1]->p.z;
		v3.x = vertices[iv3-1]->p.x;
		v3.y = vertices[iv3-1]->p.y;
		v3.z = vertices[iv3-1]->p.z;

		vc1.x = v1.x - v2.x;
		vc1.y = v1.y - v2.y;
		vc1.z = v1.z - v2.z;
		vc2.x = v1.x - v3.x;
		vc2.y = v1.y - v3.y;
		vc2.z = v1.z - v3.z;
		//float t = crossVector(&vc2,&vc1,&Norm);
		t = crossVector(&vc1,&vc2,&Norm);
		if (t>0) {
			//Norm already normalized
			trianlgesNomals[i]->x = Norm.x;
			trianlgesNomals[i]->y = Norm.y;
			trianlgesNomals[i]->z = Norm.z;


			verticesNomals[iv1-1]->x += Norm.x;
			verticesNomals[iv1-1]->y += Norm.y;
			verticesNomals[iv1-1]->z += Norm.z;
			verticesNomals[iv2-1]->x += Norm.x;
			verticesNomals[iv2-1]->y += Norm.y;
			verticesNomals[iv2-1]->z += Norm.z;
			verticesNomals[iv3-1]->x += Norm.x;
			verticesNomals[iv3-1]->y += Norm.y;
			verticesNomals[iv3-1]->z += Norm.z;

		} else {
			trianlgesNomals[i]->x = 0.0;
			trianlgesNomals[i]->y = 0.0;
			trianlgesNomals[i]->z = 0.0;
			
			verticesNomals[iv1-1]->x = 0.0;
			verticesNomals[iv1-1]->y = 0.0;
			verticesNomals[iv1-1]->z = 0.0;
			verticesNomals[iv2-1]->x = 0.0;
			verticesNomals[iv2-1]->y = 0.0;
			verticesNomals[iv2-1]->z = 0.0;
			verticesNomals[iv3-1]->x = 0.0;
			verticesNomals[iv3-1]->y= 0.0;
			verticesNomals[iv3-1]->z = 0.0;

		}

		//glNormal3f(Norm.x/t,Norm.y/t,Norm.z/t);
		//glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z);
	}
	GLfloat l = 0.0;
	Vector * tmpv = NULL;
	for ( i = 0; i<verticesCount;i++) {
		//verticesNomals[i] = new Vector;
		tmpv = verticesNomals[i];
		l = Length((*tmpv));
		if (l > 0.0) {
			verticesNomals[i]->x /= l;
			verticesNomals[i]->y /= l;
			verticesNomals[i]->z /= l;
		}
	}
}		

void  Model::calculateVerticessNormals(){
}
void Model::giveTheAvgNormOfATriangle(int tIndex,Vector & Norm ) {
	Vector avgNorm,tmpNorm;
	giveTheNormOfATriangle(tIndex,avgNorm );
	//if (Length(avgNorm)== 0.0) {
	//printf("\nTriangle %d norm is zero.",tIndex);
	//}

	int * arr=NULL,tmp  = 0, j = 0;
	tmp = triangleGetNearTriangles(tIndex, arr );
	avgNorm.x = 0.0;avgNorm.y = 0.0;avgNorm.z = 0.0;
	for (j = 0; j<tmp; j++) {
		giveTheNormOfATriangle(arr[j],tmpNorm );
		avgNorm.x = (avgNorm.x+tmpNorm.x)/2.0;
		avgNorm.y = (avgNorm.y+tmpNorm.y)/2.0;
		avgNorm.z = (avgNorm.z+tmpNorm.z)/2.0;
	}
	Norm.x = avgNorm.x;Norm.y = avgNorm.y;Norm.z = avgNorm.z;
	//if (Length(avgNorm)== 0.0) {
	//	printf("\nTriangle %d avgnorm is zero.",tIndex);
	//}
	if (arr != NULL) {
		delete [] arr;
		arr = NULL;
	}
}
void Model::giveTheNormOfATriangle(int tIndex,Vector & Norm ) {
	//Point v1,v2,v3;
	GTStriangle *  pgp= & (triangles[tIndex-1]->gt);
	//Vector vc1,vc2;
	int iv1,iv2,iv3;
	{
		int v1,v2,v3,tmp;
		tmp = v1 = v2 = v3 = -1;
		if ((edges[pgp->e1-1])->gp.beg == (edges[pgp->e2-1])->gp.beg )
			v1 = (edges[pgp->e1-1])->gp.beg ;
		else  {
			if ((edges[pgp->e1-1])->gp.beg == (edges[pgp->e2-1])->gp.fin )
				v1 = (edges[pgp->e1-1])->gp.beg ;
			else
				v1 = (edges[pgp->e1-1])->gp.fin ;
		}

		if (v1 == (edges[pgp->e2-1])->gp.beg )
			v2 = (edges[pgp->e2-1])->gp.fin ;
		else 
			v2 = (edges[pgp->e2-1])->gp.beg ;

		if (v2 == (edges[pgp->e3-1])->gp.beg )
			v3 = (edges[pgp->e3-1])->gp.fin ;
		else 
			v3 = (edges[pgp->e3-1])->gp.beg ;
		iv1 = v1;iv2 = v2;iv3 = v3;
	}
	Point v1,v2,v3;
	Vector vc1,vc2,Norm1,Norm2,Norm3;
	int count1 = 0,count2 = 0,min = 0;
	v1.x = vertices[iv1-1]->p.x;
	v1.y = vertices[iv1-1]->p.y;
	v1.z = vertices[iv1-1]->p.z;
	v2.x = vertices[iv2-1]->p.x;
	v2.y = vertices[iv2-1]->p.y;
	v2.z = vertices[iv2-1]->p.z;
	v3.x = vertices[iv3-1]->p.x;
	v3.y = vertices[iv3-1]->p.y;
	v3.z = vertices[iv3-1]->p.z;
	vc1.x = v3.x - v2.x;
	vc1.y = v3.y - v2.y;
	vc1.z = v3.z - v2.z;
	vc2.x = v1.x - v2.x;
	vc2.y = v1.y - v2.y;
	vc2.z = v1.z - v2.z;
	crossVector(&vc1,&vc2,&Norm1);
	vc1.x = v2.x - v1.x;
	vc1.y = v2.y - v1.y;
	vc1.z = v2.z - v1.z;
	vc2.x = v3.x - v1.x;
	vc2.y = v3.y - v1.y;
	vc2.z = v3.z - v1.z;
	crossVector(&vc1,&vc2,&Norm2);
	vc1.x = v1.x - v3.x;
	vc1.y = v1.y - v3.y;
	vc1.z = v1.z - v3.z;
	vc2.x = v2.x - v3.x;
	vc2.y = v2.y - v3.y;
	vc2.z = v2.z - v3.z;
	crossVector(&vc1,&vc2,&Norm3);
	Norm.x = (Norm1.x +Norm2.x +Norm3.x)/3.0;
	Norm.y = (Norm1.y +Norm2.y +Norm3.y)/3.0;
	Norm.z = (Norm1.z +Norm2.x +Norm3.z)/3.0;
}
void Model::printDetails() {
	//Vertex ** vertices;
	//modeledge ** edges;
	//modeltriangle ** triangles;
	//int verticesCount;
	//int verticesCountOrigin;
	//int verticesLimit;
	int i = 0;
	for (i =0; i<verticesCount;i++) {
		vertices[i]->printDetails();
	}
	int * arr=NULL,tmp  = 0, j = 0;
	for (i =0; i<trianglesCount;i++) {
		//tmp = triangleGetNearTriangles(int tIndex, int * arr )
		tmp = triangleGetNearTriangles(i+1, arr );
		//printf("\nTriangl no %d :",i+1);
		//for (j = 0; j< tmp; j++){
		//	printf("%d,",arr[j]);
		//} 
		if (arr != NULL) {
			delete [] arr;
			arr = NULL;
		}
	}
}
void Model::drawByTriangle() 
{
	GLfloat scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	GLfloat scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	int tmp = 0;
	Point v1,v2,v3;
	Vector vc1,vc2,Norm;


	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	int ivbk1=-1,ivbk2=-1,ivbk3=-1;
	//bool stripHead= true;
	int flipcount =  0;
	//printf("\n %d triangle count",trianglesCount);
	glDisable(GL_CULL_FACE);
	for (int i = 0; i< trianglesCount; i++ ) {
		pt = triangles[i];
		//  if ( (edges[0]->vertices[0] != edges[1]->vertices[0]) &&
		//     (edges[0]->vertices[0] != edges[1]->vertices[1]) )
		//{
		//    vertices[0]=edges[0]->vertices[0];
		//    vertices[1]=edges[0]->vertices[1];
		//}
		//else
		//{
		//    vertices[0]=edges[0]->vertices[1];
		//    vertices[1]=edges[0]->vertices[0];
		//}

		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.beg  
			&& edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e1-1]->gp.fin;
		} else {
			iv1 =  edges[pt->gt.e1-1]->gp.fin;
			iv2 =  edges[pt->gt.e1-1]->gp.beg;

		}

		if ( edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.beg  
			&& edges[pt->gt.e2-1]->gp.beg != edges[pt->gt.e1-1]->gp.fin  ) {
				iv3 =  edges[pt->gt.e2-1]->gp.beg;
		} else {
			iv3 =  edges[pt->gt.e2-1]->gp.fin;
		}


		//if ( (edges[1]->vertices[0] != edges[0]->vertices[0]) &&
		//     (edges[1]->vertices[0] != edges[0]->vertices[1]) )
		//{
		//    vertices[2]=edges[1]->vertices[0];
		//}
		//else
		//{
		//    vertices[2]=edges[1]->vertices[1];
		//}

		/*		if ( edges[pt->gt.e1-1]->gp.beg
		!= edges[pt->gt.e2-1]->gp.beg  ) {
		if ( edges[pt->gt.e1-1]->gp.beg != edges[pt->gt.e2-1]->gp.fin) {

		iv1 =  edges[pt->gt.e1-1]->gp.beg;
		iv2 =  edges[pt->gt.e1-1]->gp.fin;
		iv3 =  edges[pt->gt.e1-1]->gp.fin;
		}
		}
		else {
		if ( edges[pt->gt.e1-1]->gp.beg 
		== edges[pt->gt.e2-1]->gp.fin) {
		iv1 = edges[pt->gt.e1-1]->gp.beg;
		iv2 =  edges[pt->gt.e2-1]->gp.beg;
		iv3 =  edges[pt->gt.e1-1]->gp.fin;
		}
		else {
		iv1 = edges[pt->gt.e1-1]->gp.fin;
		iv2 =  edges[pt->gt.e2-1]->gp.beg;
		iv3 =  edges[pt->gt.e1-1]->gp.beg;
		}
		}*/


		//if ( edges[pt->gt.e1-1]->gp.beg
		//	=edges[pt->gt.e2-1]->gp.beg  ) {
		//	iv1 =  edges[pt->gt.e1-1]->gp.beg;
		//	iv2 =  edges[pt->gt.e2-1]->gp.fin;
		//	iv3 =  edges[pt->gt.e1-1]->gp.fin;
		//}
		//else {
		//	if ( edges[pt->gt.e1-1]->gp.beg 
		//		== edges[pt->gt.e2-1]->gp.fin) {
		//		iv1 = edges[pt->gt.e1-1]->gp.beg;
		//		iv2 =  edges[pt->gt.e2-1]->gp.beg;
		//		iv3 =  edges[pt->gt.e1-1]->gp.fin;
		//	}
		//	else {
		//		iv1 = edges[pt->gt.e1-1]->gp.fin;
		//		iv2 =  edges[pt->gt.e2-1]->gp.beg;
		//		iv3 =  edges[pt->gt.e1-1]->gp.beg;
		//	}
		//}
		v1.x = vertices[iv1-1]->p.x;
		v1.y = vertices[iv1-1]->p.y;
		v1.z = vertices[iv1-1]->p.z;
		v2.x = vertices[iv2-1]->p.x;
		v2.y = vertices[iv2-1]->p.y;
		v2.z = vertices[iv2-1]->p.z;
		v3.x = vertices[iv3-1]->p.x;
		v3.y = vertices[iv3-1]->p.y;
		v3.z = vertices[iv3-1]->p.z;

		//vc1.x = v2.x - v1.x;
		//vc1.y = v2.y - v1.y;
		//vc1.z = v2.z - v1.z;
		//vc2.x = v3.x - v1.x;
		//vc2.y = v3.y - v1.y;
		//vc2.z = v3.z - v1.z;

		vc1.x = v1.x - v2.x;
		vc1.y = v1.y - v2.y;
		vc1.z = v1.z - v2.z;
		vc2.x = v1.x - v3.x;
		vc2.y = v1.y - v3.y;
		vc2.z = v1.z - v3.z;
		//float t = crossVector(&vc2,&vc1,&Norm);
		float t = crossVector(&vc1,&vc2,&Norm);
		//float t = sqrt(Norm.x*Norm.x + Norm.y*Norm.y+ Norm.z*Norm.z);
		//if (t>0)
		//if ( iv1 == ivbk1 || iv1 == ivbk2 || iv1 == ivbk3 ||
		//	iv2 == ivbk1 || iv2 == ivbk2 || iv2 == ivbk3 ||
		//	iv3 == ivbk1 || iv3 == ivbk2 || iv3 == ivbk3)
		//	flipcount++;
		//else
		//	flipcount = 0;

		glBegin(GL_TRIANGLES);
		glNormal3f(Norm.x/t,Norm.y/t,Norm.z/t);
		glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z);
		//if (flipcount %2 == 0) {
		//	 glNormal3f(Norm.x/t,Norm.y/t,Norm.z/t);
		//	glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z); 
		//}
		//else {
		//		glNormal3f(-Norm.x/t,-Norm.y/t,-Norm.z/t);
		//		glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v3.x,v3.y,v3.z);
		//		printf("\n%d inverse triangle",i);
		//}
		glEnd();			
		//ivbk1=iv1,ivbk2=iv2,ivbk3=iv3;
	}

	glPopMatrix();
}		


void Model::drawByTriangleBK() 
{
	GLfloat scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	GLfloat scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	int tmp = 0;
	Point v1,v2,v3;
	Vector vc1,vc2,Norm;


	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	int ivbk1=-1,ivbk2=-1,ivbk3=-1;
	//bool stripHead= true;
	int flipcount =  0;
	//printf("\n %d triangle count",trianglesCount);
	for (int i = 0; i< trianglesCount; i++ ) {
		pt = triangles[i];
		if ( edges[pt->gt.e1-1]->gp.beg
			==edges[pt->gt.e2-1]->gp.beg  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e2-1]->gp.fin;
				iv3 =  edges[pt->gt.e1-1]->gp.fin;
		}
		else {
			if ( edges[pt->gt.e1-1]->gp.beg 
				== edges[pt->gt.e2-1]->gp.fin) {
					iv1 = edges[pt->gt.e1-1]->gp.beg;
					iv2 =  edges[pt->gt.e2-1]->gp.beg;
					iv3 =  edges[pt->gt.e1-1]->gp.fin;
			}
			else {
				iv1 = edges[pt->gt.e1-1]->gp.fin;
				iv2 =  edges[pt->gt.e2-1]->gp.beg;
				iv3 =  edges[pt->gt.e1-1]->gp.beg;
			}
		}
		v1.x = vertices[iv1-1]->p.x;
		v1.y = vertices[iv1-1]->p.y;
		v1.z = vertices[iv1-1]->p.z;
		v2.x = vertices[iv2-1]->p.x;
		v2.y = vertices[iv2-1]->p.y;
		v2.z = vertices[iv2-1]->p.z;
		v3.x = vertices[iv3-1]->p.x;
		v3.y = vertices[iv3-1]->p.y;
		v3.z = vertices[iv3-1]->p.z;

		vc1.x = v2.x - v1.x;
		vc1.y = v2.y - v1.y;
		vc1.z = v2.z - v1.z;
		vc2.x = v3.x - v1.x;
		vc2.y = v3.y - v1.y;
		vc2.z = v3.z - v1.z;
		float t = crossVector(&vc2,&vc1,&Norm);
		//float t = sqrt(Norm.x*Norm.x + Norm.y*Norm.y+ Norm.z*Norm.z);
		//if (t>0)
		if ( iv1 == ivbk1 || iv1 == ivbk2 || iv1 == ivbk3 ||
			iv2 == ivbk1 || iv2 == ivbk2 || iv2 == ivbk3 ||
			iv3 == ivbk1 || iv3 == ivbk2 || iv3 == ivbk3)
			flipcount++;
		else
			flipcount = 0;

		glBegin(GL_TRIANGLES);
		if (flipcount %2 == 0) {
			glNormal3f(Norm.x/t,Norm.y/t,Norm.z/t);
			glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v3.x,v3.y,v3.z); 
		}
		else {
			glNormal3f(-Norm.x/t,-Norm.y/t,-Norm.z/t);
			glVertex3f(v2.x,v2.y,v2.z);glVertex3f(v1.x,v1.y,v1.z);glVertex3f(v3.x,v3.y,v3.z);
			//printf("\n%d inverse triangle",i);
		}
		glEnd();			
		ivbk1=iv1,ivbk2=iv2,ivbk3=iv3;
	}

	glPopMatrix();
}		
void Model::drawByTriangle2() 
{
	GLfloat scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	GLfloat scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);
	glBegin(GL_TRIANGLES);

	modeltriangle * pt;
	int iv1=-1,iv2=-1,iv3=-1;
	Vector Norm;
	Point v1,v2,v3;

	for (int i = 0; i< trianglesCount; i++ ) {
		pt = triangles[i];
		if ( edges[pt->gt.e1-1]->gp.beg
			==edges[pt->gt.e2-1]->gp.beg  ) {
				iv1 =  edges[pt->gt.e1-1]->gp.beg;
				iv2 =  edges[pt->gt.e2-1]->gp.fin;
				iv3 =  edges[pt->gt.e1-1]->gp.fin;
		}
		else {
			if ( edges[pt->gt.e1-1]->gp.beg 
				== edges[pt->gt.e2-1]->gp.fin) {
					iv1 = edges[pt->gt.e1-1]->gp.beg;
					iv2 =  edges[pt->gt.e2-1]->gp.beg;
					iv3 =  edges[pt->gt.e1-1]->gp.fin;
			}
			else {
				iv1 = edges[pt->gt.e1-1]->gp.fin;
				iv2 =  edges[pt->gt.e2-1]->gp.beg;
				iv3 =  edges[pt->gt.e1-1]->gp.beg;
			}
		}
		v1.x = vertices[iv1-1]->p.x;
		v1.y = vertices[iv1-1]->p.y;
		v1.z = vertices[iv1-1]->p.z;
		v2.x = vertices[iv2-1]->p.x;
		v2.y = vertices[iv2-1]->p.y;
		v2.z = vertices[iv2-1]->p.z;
		v3.x = vertices[iv3-1]->p.x;
		v3.y = vertices[iv3-1]->p.y;
		v3.z = vertices[iv3-1]->p.z;

		giveTheAvgNormOfATriangle(i+1, Norm );
		glNormal3f(Norm.x,Norm.y,Norm.z);
		//glNormal3f(0,0,0);
		glVertex3f(v1.x,v1.y,v1.z);
		glVertex3f(v2.x,v2.y,v2.z);
		glVertex3f(v3.x,v3.y,v3.z);

	}
	glEnd();

	glPopMatrix();
}

int Model::addATriangle(GTStriangle * pgp,int nindex,int nattrib ){
	//addATriangleToTlist(GTStriangle * pgt,int nindex,int nattrib);
	modeltriangle * tmpp = addATriangleToTlist(pgp,nindex,nattrib );
	int v1,v2,v3,tmp;
	tmp = v1 = v2 = v3 = -1;
	//if pgp->e1
	if ((edges[pgp->e1-1])->gp.beg == (edges[pgp->e2-1])->gp.beg )
		v1 = (edges[pgp->e1-1])->gp.beg ;
	else  {
		if ((edges[pgp->e1-1])->gp.beg == (edges[pgp->e2-1])->gp.fin )
			v1 = (edges[pgp->e1-1])->gp.beg ;
		else
			v1 = (edges[pgp->e1-1])->gp.fin ;
	}

	if (v1 == (edges[pgp->e2-1])->gp.beg )
		v2 = (edges[pgp->e2-1])->gp.fin ;
	else 
		v2 = (edges[pgp->e2-1])->gp.beg ;

	if (v2 == (edges[pgp->e3-1])->gp.beg )
		v3 = (edges[pgp->e3-1])->gp.fin ;
	else 
		v3 = (edges[pgp->e3-1])->gp.beg ;
	vertices[v1-1]->addATriangle(tmpp); 
	vertices[v2-1]->addATriangle(tmpp); 
	vertices[v3-1]->addATriangle(tmpp); 
	return 0;
};
int Model::addAnEdge(GTSedgePair *  pgp,int nindex,int nattrib ){
	modeledge * tmpp = addAnEdgeToElist(pgp,nindex,nattrib );
	//vertices[(pgp->gp.beg)-1]->addAnEdge(pgp); 
	//vertices[(pgp->gp.fin)-1]->addAnEdge(pgp); 
	vertices[(pgp->beg)-1]->addAnEdge(tmpp); 
	vertices[(pgp->fin)-1]->addAnEdge(tmpp); 

	return 0;
}
//int Model::triangleGetNearTriangles(int tIndex, int * arr ){
int Model::triangleGetNearTriangles(int tIndex, int * & arr ){
	//GTSedgePair *pgp,gp;
	GTStriangle *  pgp= & (triangles[tIndex-1]->gt);
	int count = 0;
	int v1,v2,v3,tmp;
	tmp = v1 = v2 = v3 = -1;
	//if pgp->e1
	if ((edges[pgp->e1-1])->gp.beg == (edges[pgp->e2-1])->gp.beg )
		v1 = (edges[pgp->e1-1])->gp.beg ;
	else  {
		if ((edges[pgp->e1-1])->gp.beg == (edges[pgp->e2-1])->gp.fin )
			v1 = (edges[pgp->e1-1])->gp.beg ;
		else
			v1 = (edges[pgp->e1-1])->gp.fin ;
	}

	if (v1 == (edges[pgp->e2-1])->gp.beg )
		v2 = (edges[pgp->e2-1])->gp.fin ;
	else 
		v2 = (edges[pgp->e2-1])->gp.beg ;

	if (v2 == (edges[pgp->e3-1])->gp.beg )
		v3 = (edges[pgp->e3-1])->gp.fin ;
	else 
		v3 = (edges[pgp->e3-1])->gp.beg ;

	tmp = vertices[v1-1]->tCount +vertices[v2-1]->tCount
		+ vertices[v3-1]->tCount;
	if (tmp > 0)
		arr = new int [tmp];
	else {
		printf("\nError in Model::triangleGetNearTriangles(int tIndex, int * arr ) ");
		exit(0);
	}

	// omit repeated vertices
	int i = 0,j = 0;
	bool flag_exist = false;
	for ( i = 0; i<vertices[v1-1]->tCount; i++) {
		if (count == 0) {
			arr[count] = vertices[v1-1]->connectedTriangles[i];
			count++;
		} else {
			for (j = 0; j<count; j++) {
				if (arr[j] == vertices[v1-1]->connectedTriangles[i] ) {
					flag_exist = true; break;
				}
			}
			if ( ! flag_exist )  {
				arr[count] = vertices[v1-1]->connectedTriangles[i];
				count++;
			}
			flag_exist = false;
		}
	}
	for ( i = 0; i<vertices[v2-1]->tCount; i++) {
		if (count == 0) {
			arr[count] = vertices[v2-1]->connectedTriangles[i];
			count++;
		} else {
			for (j = 0; j<count; j++) {
				if (arr[j] == (vertices[v2-1]->connectedTriangles[i]) ) {
					flag_exist = true; break;
				}
			}
			if ( ! flag_exist )  {
				arr[count] = vertices[v2-1]->connectedTriangles[i];
				count++;
			}
			flag_exist = false;
		}
	}
	for ( i = 0; i<vertices[v3-1]->tCount; i++) {
		if (count == 0) {
			arr[count] = vertices[v3-1]->connectedTriangles[i];
			count++;
		} else {
			for (j = 0; j<count; j++) {
				if (arr[j] == vertices[v3-1]->connectedTriangles[i] ) {
					flag_exist = true; break;
				}
			}
			if ( ! flag_exist )  {
				arr[count] = vertices[v3-1]->connectedTriangles[i];
				count++;
			}
			flag_exist = false;
		}
	}
	return count;
}
modeltriangle * Model::addATriangleToTlist(GTStriangle * pgt,int nindex,int nattrib) {
	int success = -1;
	int i = 0;
	if (trianglesCount + 1 > trianglesLimit) {
		modeltriangle ** tmp;
		tmp = (modeltriangle **) malloc ( sizeof(modeltriangle * ) * trianglesLimit * 2);
		for (i = 0; i<trianglesCount; i++) {
			tmp[i] = triangles[i];
		}
		tmp[i] = new modeltriangle(pgt,nindex,nattrib);
		for (i = trianglesCount+1; i< trianglesLimit * 2; i++)
			tmp[i] = NULL;
		delete [] triangles;
		triangles = tmp;
		trianglesLimit = trianglesLimit * 2;
	} else 
		triangles[trianglesCount] = new modeltriangle(pgt,nindex,nattrib);
	++trianglesCountOrigin;
	//????????????????
	return triangles[trianglesCount++];

};
modeledge * Model::addAnEdgeToElist(_edgePair* pgp,int nindex,int nattrib ){
	int success = -1;
	int i = 0;
	if (edgesCount + 1 > edgesLimit) {
		modeledge ** tmp;
		tmp = (modeledge **) malloc ( sizeof(modeledge * ) * edgesLimit * 2);
		for (i = 0; i<edgesCount; i++) {
			tmp[i] = edges[i];
		}
		tmp[i] = new modeledge(pgp,nindex,nattrib);
		for (i = edgesCount+1; i< edgesLimit * 2; i++)
			tmp[i] = NULL;
		delete [] edges;
		edges = tmp;
		edgesLimit = edgesLimit * 2;
	} else 
		edges[edgesCount] = new modeledge(pgp,nindex,nattrib);
	++edgesCountOrigin;
	//????????????????
	return edges[edgesCount++];
}

void Model::drawByEdges() 
{
	float scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	float scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);

	int tmp = 0;
	glPointSize(1.0);
	glBegin(GL_LINES );
	int i = 0;
	modeledge * mlp;
	Vertex * vp;
	for (i = 0; i< edgesCount;i++) {
		//glVertex3f(vertices[i]->p.x,vertices[i]->p.y,vertices[i]->p.z);
		//edges[i]
		mlp = edges[i];
		vp = vertices[mlp->gp.beg-1];
		glVertex3f(vp->p.x,vp->p.y,vp->p.z);
		vp = vertices[mlp->gp.fin-1];
		glVertex3f(vp->p.x,vp->p.y,vp->p.z);
	}
	glEnd();
	glPopMatrix();
}


void Model::drawByVertices() 
{
	float scale1,scale2,scale3;
	scale1 = OBJ_SIZE/(xmax - xmin);
	scale2 = OBJ_SIZE/(ymax - ymin);
	scale3 = OBJ_SIZE/(zmax - zmin);
	float scale = 
		(
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin))<OBJ_SIZE/(zmax - zmin)
		)
		?
		((OBJ_SIZE/(xmax - xmin)<OBJ_SIZE/(ymax - ymin))
		?OBJ_SIZE/(xmax - xmin):OBJ_SIZE/(ymax - ymin)):OBJ_SIZE/(zmax - zmin);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glTranslatef(-(xmin+xmax)/2,-(ymin+ymax)/2,-(zmin+zmax)/2);

	int tmp = 0;
	glPointSize(1.0);
	glBegin(GL_POINTS );
	int i = 0;
	//for (i = 0; i< verticesCount;i++) {
	for (i = 0; i< verticesCount;i++) {
		glVertex3f(vertices[i]->p.x,vertices[i]->p.y,vertices[i]->p.z);
	}
	glEnd();
	glPopMatrix();
}
//void Model::initFromCurveList(curvelist * pcl) {
//	int i = 0;
//	for (i = 0; i< pcl->vertex_count;i++) {
//		addAVertexToVlist(pcl->vertices[i], i+1, COMMON_VERTEX );
//	}
//
//	//for (i = 0; i< pcl->vertex_count;i++) {
//	//	addAVertexToVlist(pcl->vertices[i], i+1, COMMON_VERTEX );
//	//}
////int Model::addAnEdge(GTSedgePair * pgp,int nindex,int nattrib ){
////int Model::addAnEdgeToElist(GTSedgePair * pgp,int nindex,int nattrib ){
//	for (i = 0; i< pcl->edge_count;i++) {
//		addAnEdge(pcl->edges[i], i+1, VALID_EDGE );
//	}
//	//VALID_TRIANGLE
//	for (i = 0; i< pcl->triangle_count;i++) {
//		//addATriangleToTlist(pcl->triangles[i], i+1, VALID_TRIANGLE );
//		addATriangle(pcl->triangles[i], i+1, VALID_TRIANGLE );
//	}
//
//	xmin=pcl->xmin;xmax=pcl->xmax;ymin=pcl->ymin;
//	ymax=pcl->ymax;zmin=pcl->zmin;zmax=pcl->zmax;
//	OBJ_SIZE=pcl->OBJ_SIZE;
//}
int Model::addAVertexToVlist( Point *  p, int ci, int attr) {
	int success = -1;
	int i = 0;
	if (verticesCount + 1 > verticesLimit) {
		Vertex ** tmp;
		tmp = (Vertex **) malloc ( sizeof(Vertex * ) * verticesLimit * 2);
		for (i = 0; i<verticesCount; i++) {
			tmp[i] = vertices[i];
		}
		tmp[i] = new Vertex(p,ci,attr);
		for (i = verticesCount+1; i< verticesLimit * 2; i++)
			tmp[i] = NULL;
		delete [] vertices;
		vertices = tmp;
		verticesLimit = verticesLimit * 2;
	} else 
		vertices[verticesCount] = new Vertex(p,ci,attr);
	++verticesCountOrigin;
	return ++verticesCount;
};
Model::~Model() {
	int i = 0;
	for (i =0;i <verticesLimit; i++) {
		if (vertices[i] != NULL) {
			vertices[i]->~Vertex();
			//delete[] vertices[i];
		}
	}
	delete[] vertices;
	// we don't need collect garbarge for edge and triange objects
	///?????? free pinters without dynamic mem-alloc?
	for (i =0;i <edgesLimit; i++) {
		if (edges[i] != NULL) {
			free(edges[i]);
			//delete[] vertices[i];
		}
	}
	delete[] edges;

	for (i =0;i <trianglesLimit; i++) {
		if (triangles[i] != NULL) {
			free(triangles[i]);
			//delete[] vertices[i];
		}
	}
	delete[] triangles;
}
Model::Model() {
	//OBJ_SIZE = 32.0;
	verticesCount = 0;
	verticesCountOrigin = 0;
	verticesLimit = 10;
	vertices = (Vertex **) malloc ( sizeof(Vertex * ) * verticesLimit);
	int i = 0;
	for (i =0;i <verticesLimit; i++)
		vertices[i] = NULL;
	//edges
	//class modeledge
	//class modeltriangle
	edgesCount = 0;
	edgesCountOrigin = 0;
	edgesLimit = 10;
	edges = (modeledge **) malloc ( sizeof(modeledge * ) * edgesLimit);
	//int i = 0;
	for (i =0;i <edgesLimit; i++)
		edges[i] = NULL;

	trianglesCount = 0;
	trianglesCountOrigin = 0;
	trianglesLimit = 10;
	triangles = (modeltriangle **) malloc ( sizeof(modeltriangle * ) * trianglesLimit);
	//int i = 0;
	for (i =0;i <trianglesLimit; i++)
		triangles[i] = NULL;
}
//void Model::initFromFile(char * fn) {
//	char line[100];
//	FILE * fp;	int i;	GTSedgePair tmpep; int e1=0,e2=0;	GTStriangle tmpt;int t1,t2,t3;
//	if( (fp=fopen(fn,"r")) == NULL ) {
//		printf( "The file x_w was not opened\n" );
//		exit(0);
//	}
//	int nc = 0;
//	int nv=0,ns=0,nt=0;
//		memset(line,0,100);
//	if( fgets( line, 100, fp ) == NULL) {
//		if (feof(fp))  {
//			printf("\nEmpty file. \n");
//			exit(0);
//		}
//		else {
//			printf( "\nfgets error\n" );
//			exit(0);
//		}
//	}
//	nc=sscanf(line,"%d %d %d",&nv,&ns,&nt);
//	printf("\n%d %d %d \n",nv,ns,nt);
//	if (nc != 3 ) {
//		printf("\n%d %d %d \n",nv,ns,nt);
//		printf("\nData file header error \n");
//		exit(0);
//	}
//	float x =0.0,y =0.0,z =0.0;
//	nc=sscanf(line,"%f %f %f",&x,&y,&z);
//	if (nc != 3) {
//		printf( "\nFile format error\n" );
//		exit(0);
//	}
//	// i =0;
//	Point tmpp;
//	tmpp.x = x; tmpp.y = y ; tmpp.z = z;
//	//mp->addAVertex(tmpp);
//	xmin = x;	ymin = y;	zmin = z;
//	xmax = x;	ymax = y;	zmax = z;
//	//addAVertexToVlist(&tmpp,1,COMMON_VERTEX);
//
//
//	for ( i = 1;i < nv ;i++ ) {
//		//for (int m = 0;m<100; m++) 
//		//line[m] = '\0';
//		memset(line,0,100);
//		if( fgets( line, 100, fp ) == NULL) {
//			if (feof(fp)) break;
//			else {
//				printf( "\nfgets error\n" );
//				exit(0);
//			}
//		}
//		nc=sscanf(line,"%f %f %f",&x,&y,&z);
//		//printf("\n%s",line);
//		if (nc != 3) {
//			printf("\n vertex %s",line);
//			printf( "\nFile format error\n" );
//			exit(0);
//		}
//		tmpp.x = x; tmpp.y = y ; tmpp.z = z;
//		//addAVertexToVlist(&tmpp,i+1,COMMON_VERTEX);
//		xmin = (xmin < x)?xmin:x;
//		ymin = (ymin < y)?ymin:y;
//		zmin = (zmin < z)?zmin:z;
//		xmax = (xmax > x)?xmax:x;
//		ymax = (ymax > y)?ymax:y;
//		zmax = (zmax > z)?zmax:z;
//	}
//	printf( "\nEnd of verties%d, %f ,%f , %f\n",i,x,y,z );
//
//	for ( i = 0;i < ns ;i++ ) {
//		memset(line,0,100);
//		if( fgets( line, 100, fp ) == NULL) {
//			if (feof(fp)) break;
//			else {
//				printf("\n %s edge %d",line,i);
//				printf( "\n fgets error\n" );
//				exit(0);
//			}
//		}
//		if (i == 0) printf("\n %s edge %d",line,i);
//		nc=sscanf(line,"%d %d",&e1,&e2);
//		if (nc != 2) {
//			printf("%d %d ",e1,e2);
//			printf("\n %s, %d ",line,i);
//			printf( "\nEdges? File format error\n" );
//			//exit(0);
//			return;
//		}
//		//mp->addAnEdge(--e1,--e2);
//		tmpep.beg = e1,tmpep.fin = e2;
//		//addAnEdge(&tmpep,i+1,VALID_EDGE);
//	
//	/*	tmpe1 = ptopd( (mp->vertices[e1])->p,(mp->vertices[e2])->p );
//		if (minedge == 0.0)
//			minedge = tmpe1;
//		
//		minedge = (minedge < tmpe1 )?minedge:tmpe1;
//		maxedge = (maxedge > tmpe1 )?maxedge:tmpe1;*/ 
//	}
//printf( "\nEnd of edges %d\n",i );
//
//
//	for ( i = 0;i < nt ;i++ ) {
//		memset(line,0,100);
//		if( fgets( line, 100, fp ) == NULL) {
//			if (feof(fp)) break;
//			else {
//				printf( "\nfgets error\n" );
//				exit(0);
//			}
//		}
//		nc=sscanf(line,"%d %d %d",&t1,&t2,&t3);
//		if (nc != 3) {
//			printf( "\nFile format error\n" );
//			exit(0);
//		}
//		tmpt.e1 = t1,tmpt.e1 = t2,tmpt.e1 = t3;
//		addATriangle(&tmpt,i+1,VALID_TRIANGLE);
//
//	}
//	fclose(fp);
//
//
//
//
//
//
//	//for (i = 0; i< pcl->edge_count;i++) {
//	//	addAnEdge(pcl->edges[i], i+1, VALID_EDGE );
//	//}
//	////VALID_TRIANGLE
//	//for (i = 0; i< pcl->triangle_count;i++) {
//	//	//addATriangleToTlist(pcl->triangles[i], i+1, VALID_TRIANGLE );
//	//	addATriangle(pcl->triangles[i], i+1, VALID_TRIANGLE );
//	//}
//
//	//xmin=pcl->xmin;xmax=pcl->xmax;ymin=pcl->ymin;
//	//ymax=pcl->ymax;zmin=pcl->zmin;zmax=pcl->zmax;
//	//OBJ_SIZE=pcl->OBJ_SIZE;
//}

void Model::initFromFile (char * fn){
	//printf("\nread file");
	//GLfloat xmin,xmax,ymin,ymax,zmin,zmax;
	//xmin = xmax= ymin= ymax= zmin= zmax = 0;
	GLfloat x=0.0, y=0.0, z=0.0;
	GLfloat minedge=0.0,maxedge=0.0,tmpe1=0.0,tmpe2=0.0;
	int nv=0.0,ns=0.0,nt=0.0;
	int e1=0.0,e2=0.0;
	int t1=0,t2=0,t3=0;
	GTSedgePair tmpep;GTStriangle tmpt;
	Point tmpp;
	tmpp.x = 0.0; tmpp.y = 0.0 ; tmpp.z = 0.0;
	tmpep.beg = 0; tmpep.fin =0;
	tmpt.e1 =0;tmpt.e2 =0;tmpt.e3 =0;



	//FILE *stream;
	char line[100];
	FILE * fp;
	if( (fp=fopen(fn,"r")) == NULL ) {
		printf( "The file was not opened\n" );
		exit(0);
	}
	if( fgets( line, 100, fp ) == NULL) {
		if (feof(fp))  {
			printf("\nEmpty file. \n");
			exit(0);
		}
		else {
			printf( "\nfgets error\n" );
			exit(0);
		}
	}
	int nc = 0;
	nv=0,ns=0,nt=0;
	nc=sscanf(line,"%d %d %d",&nv,&ns,&nt);
	if (nc != 3 ) {
		printf("\nData file header error \n");
		exit(0);
	}

	memset(line,0,100);
	if( fgets( line, 100, fp ) == NULL) {
		if (feof(fp)) 
			printf( "\nFile error\n" );
		else {
			printf( "\nfgets error\n" );
		}
		exit(0);
	}
	x =0.0;y =0.0;z =0.0;
	nc=sscanf(line,"%f %f %f",&x,&y,&z);
	if (nc != 3) {
		printf( "\nFile format error\n" );
		exit(0);
	}
	tmpp.x = x; tmpp.y = y ; tmpp.z = z;
	//mp->addAVertex(tmpp);
	addAVertexToVlist(&tmpp,1,COMMON_VERTEX);
	xmin = x;	ymin = y;	zmin = z;
	xmax = x;	ymax = y;	zmax = z;
	int i;
	for ( i = 1;i < nv ;i++ ) {
		memset(line,0,100);
		if( fgets( line, 100, fp ) == NULL) {
			if (feof(fp)) break;
			else {
				printf( "\nfgets error\n" );
				exit(0);
			}
		}
		nc=sscanf(line,"%f %f %f",&x,&y,&z);
		if (nc != 3) {
			printf( "\nFile format error\n" );
			exit(0);
		}
		tmpp.x = x; tmpp.y = y ; tmpp.z = z;
		//mp->addAVertex(tmpp);
		addAVertexToVlist(&tmpp,i+1,COMMON_VERTEX);
		xmin = (xmin < x)?xmin:x;
		ymin = (ymin < y)?ymin:y;
		zmin = (zmin < z)?zmin:z;
		xmax = (xmax > x)?xmax:x;
		ymax = (ymax > y)?ymax:y;
		zmax = (zmax > z)?zmax:z;
	}

	for ( i = 0;i < ns ;i++ ) {
		memset(line,0,100);
		if( fgets( line, 100, fp ) == NULL) {
			if (feof(fp)) break;
			else {
				printf( "\nfgets error\n" );
				exit(0);
			}
		}
		nc=sscanf(line,"%d %d ",&e1,&e2);
		if (nc != 2) {
			printf( "\nFile format error\n" );
			exit(0);
		}
		//mp->addAnEdge(--e1,--e2);
		tmpep.beg = e1,tmpep.fin = e2;
		addAnEdge(&tmpep,i+1,VALID_EDGE);
		if (minedge == 0.0)
			minedge = tmpe1;

		minedge = (minedge < tmpe1 )?minedge:tmpe1;
		maxedge = (maxedge > tmpe1 )?maxedge:tmpe1;
	}
	for ( i = 0;i < nt ;i++ ) {
		memset(line,0,100);
		if( fgets( line, 100, fp ) == NULL) {
			if (feof(fp)) break;
			else {
				printf( "\nfgets error\n" );
				exit(0);
			}
		}
		nc=sscanf(line,"%d %d %d",&t1,&t2,&t3);
		//sscanf(
		if (nc != 3) {
			printf( "\nFile format error\n" );
			//exit(0);
			return;
		}
		//if (i == 0) printf("%d %d %d",t1,t2,t3);
		tmpt.e1 = t1,tmpt.e2 = t2,tmpt.e3 = t3;
		//if (i == 0) printf("%d %d %d",tmpt.e1,tmpt.e2,tmpt.e3);
		addATriangle(&tmpt,i+1,VALID_TRIANGLE);
		//

	}
	fclose(fp);
	printf("\ndone");
}
