//============================================================================
// Name        : Basics.h
// Author      : Zhikai
// Version     :
// Copyright   : (c) 2010 2015 Zhikai Wang/www.heteroclinic.net
// Description : Basic implementation of math functions
//============================================================================
#ifndef __BASICS
#define __BASICS
//#include <windows.h>
//#include <stdlib.h>
//#include <mmsystem.h>
//#include <QtOpenGL>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>


//#include "timing.h"
#define Length(v)  sqrt(v.x*v.x+v.y*v.y+v.z*v.z)	// Vector length

#define LCHARS			300
#define CURVE_POINTS	400
#define CURVE_NO	400
#define GRID_MODE 1
#define SURF_MODE 2
#define MESH_MODE 3
#define LIGHT_MODE 4
#define SINGLE_MODE 5
#define PART_MODE 7
#define AVG_MODE 6
#define LRZ_MODE 8
#define LIGHT2_MODE 9

#define SINGLE_ORBIT	0
#define SINGLE_T		1
#define SINGLE_GEO		2
//#define ARC_STEP	200

#define BORDER_VERTEX 1
#define COMMON_VERTEX 2
#define VALID_EDGE 3
#define VALID_TRIANGLE 4
#define INVALID -1
#define NO_OF_DRAW_MODE 2
#define NO_OF_SIMPLIFY_MODE 2
#define D_ON 0
#define S_ON 1
#define ADJ_SCALE 0
#define ADJ_SPEED 1
#define ADJ_ANGLE 2
#define COLLOCATION_PTS 1

//#define DRAW_BY_MODEL 0
extern int DRAW_BY_MODEL;
extern int DS_SWITCH;
extern char * read_file;
extern char * write_file;
extern char * error_file;
extern float ROTATION_ANGLE ;
extern float SHIP_SPEED ;
extern int ADJ;
//#define DRAW_BY_MODEL 0
extern int SIMPLIFY_MODE;
extern bool REAL_SCALE;
extern bool showAxis;
extern bool	drawPartial;
extern bool draw_transparency;
extern float shearm[16];
//#define OBJ_SIZE		32
//GLfloat  OBJ_SIZE = 32.0;
typedef struct _Point {
	float x, y, z;
} Point, Vector, * p_Point;

typedef struct _edgePair {
	int beg;
	int fin;
} GTSedgePair, * p_GTSedgePair;

typedef struct _triangle {
	int e1;
	int e2;
	int e3;
} GTStriangle,* p_GTStriangle;

typedef struct _AutoPoint {
	float t;
	Point p;
	float arclength;
} APoint,* p_APoint;
extern  float   tolerance_radius;
void DrawText(int x, int y, char* s, float r, float g, float b);
float ptopd ( Point p1, Point p2);
float crossVector (Vector  * v, Vector * w, Vector * crossVector);
void loadTexture( void );
template <class T> 
T simpsonIntegrate( int N,T start_value,T end_value,  T(* func)(T));
template <class T> 
T lagrangeInterpolate( int n,T itpv,T * weight,T * base);
#endif
