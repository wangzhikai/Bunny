//============================================================================
// Name        : modeledge.h
// Author      : Zhikai
// Version     :
// Copyright   : (c) 2010 2015 Zhikai Wang/www.heteroclinic.net
// Description : Mock of GTS with limited new features.
//============================================================================
#ifndef __EDGE
#define __EDGE
#include "basics.h"
class modeledge {
public:
	modeledge(_edgePair* pgp,int nindex,int nattrib);
GTSedgePair gp;
int index;
int attrib;
};
/*
modeledge::modeledge(_edgePair* pgp,int nindex,int nattrib){
	gp.beg = pgp->beg;
	gp.fin = pgp->fin;
	index = nindex;
	attrib = nattrib;
}
*/
#endif
