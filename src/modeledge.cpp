#include "modeledge.h"
modeledge::modeledge(_edgePair* pgp,int nindex,int nattrib){
	gp.beg = pgp->beg;
	gp.fin = pgp->fin;
	index = nindex;
	attrib = nattrib;
}
