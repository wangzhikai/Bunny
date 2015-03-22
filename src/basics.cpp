//============================================================================
// Name        : Basics.cpp
// Author      : Zhikai
// Version     :
// Copyright   : (c) 2010 2015 Zhikai Wang/www.heteroclinic.net
// Description : Basic implementation of math functions
//============================================================================
#include "basics.h"
template <class T> 
T lagrangeInterpolate( int n,T itpv,T * weight,T * base) {
	T  result;
	int i = 0, j= 0, m= 0;
	if (n < 0 || base == NULL ||weight==NULL ) {
		printf("\nVariables problem in lagrangeInterpolate.");
		exit(0);
		//return 0;
	}
	else {
		//		T dividor = (T)0.0;
		//T divident = (T)0.0;
		T * l = (T *)malloc(sizeof(T)* n); 
		for ( i = 0 ; i<n ; i++) {
			l[i] = 1.0;
			for ( j=0; j<n; j++) {
				if (j != i)
					l[i] *= (itpv - weight[j])/(weight[i] - weight[j]);
			}
		}
		result=0.0;
		for ( j=0; j<n; j++) 
			result += l[j] * base[j];
		return result;
	}
}
template <class T> 
T simpsonIntegrate( int N,T start_value,T end_value, 
				   T(* func)(T)) {
	T h = (end_value - start_value) / N;
	int i =   0;
	T sum  = (T)0.0;
	T x = start_value,xminusone = start_value,xminushalf = start_value;
	for ( i =1; i<=N; i++) {
		x = i*h + start_value;
		xminusone = x - h;
		xminushalf = x - h/2.0;
		sum += ( func(xminusone) + func(x) + 4.0 * func(xminushalf) ) * h/6.0;
	}
	return sum;
}

float ptopd ( Point p1, Point p2) {
	return sqrt( (p1.x-p2.x)*(p1.x-p2.x)
		+(p1.y-p2.y)*(p1.y-p2.y)
		+(p1.z-p2.z)*(p1.z-p2.z) );
}
float ptopd ( Point * p1, Point * p2) {
	return sqrt( (p1->x-p2->x)*(p1->x-p2->x)
		+(p1->y-p2->y)*(p1->y-p2->y)
		+(p1->z-p2->z)*(p1->z-p2->z) );
}
float crossVector (Vector  * v, Vector * w, Vector * crossVector)
{
	float cosinTheta, sinTheta, crossVectorLength;
	// dot production v->w
	float vw = v->x*w->x + v->y*w->y + v->z*w->z;

	cosinTheta = vw / (Length((*v))*Length((*w)));
	sinTheta = sqrt(1-cosinTheta*cosinTheta);
	crossVectorLength = Length((*v))*Length((*w))*sinTheta;
	
	// Normalize it
	crossVector->x = (v->y*w->z - v->z*w->y) / crossVectorLength;
	crossVector->y = (v->z*w->x - v->x*w->z) / crossVectorLength;
	crossVector->z = (v->x*w->y - v->y*w->x) / crossVectorLength;

	//crossVector->x = (v->y*w->z - v->z*w->y) ;
	//crossVector->y = (v->z*w->x - v->x*w->z) ;
	//crossVector->z = (v->x*w->y - v->y*w->x) ;

	return crossVectorLength;
}

//GLdouble crossVector (Vector  * v, Vector * w, Vector * crossVector)
//{
//	GLdouble cosinTheta, sinTheta, crossVectorLength;
//	// dot production v->w
//	GLdouble vw = v->x*w->x + v->y*w->y + v->z*w->z;
//
//	cosinTheta = vw / (Length((*v))*Length((*w)));
//	sinTheta = sqrt(1-cosinTheta*cosinTheta);
//	crossVectorLength = Length((*v))*Length((*w))*sinTheta;
//	
//	// Normalize it
//	crossVector->x = (v->y*w->z - v->z*w->y) / crossVectorLength;
//	crossVector->y = (v->z*w->x - v->x*w->z) / crossVectorLength;
//	crossVector->z = (v->x*w->y - v->y*w->x) / crossVectorLength;
//
//	return crossVectorLength;
//}
