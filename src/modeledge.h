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
