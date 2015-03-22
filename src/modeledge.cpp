//============================================================================
// Name        : modeledge.cpp
// Author      : Zhikai
// Version     :
// Copyright   : (c) 2010 2015 Zhikai Wang/www.heteroclinic.net
// Description : Mock of GTS with limited new features.
//============================================================================
#include "modeledge.h"
modeledge::modeledge(_edgePair* pgp,int nindex,int nattrib){
	gp.beg = pgp->beg;
	gp.fin = pgp->fin;
	index = nindex;
	attrib = nattrib;
}
