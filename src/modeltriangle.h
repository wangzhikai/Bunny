#ifndef __TRIANGLE
#define __TRIANGLE
#include "basics.h"
/*
typedef struct _triangle {
	int e1;
	int e2;
	int e3;
} GTStriangle,* p_GTStriangle;
*/
class modeltriangle {
public:
	modeltriangle(_triangle* pgt,int nindex,int nattrib){
	gt.e1 = pgt->e1;
	gt.e2 = pgt->e2;
	gt.e3 = pgt->e3;
	index = nindex;
	attrib = nattrib;
};
GTStriangle gt;
int index;
int attrib;
};

#endif
