/*DevGUI v2.2.0*/

#ifndef _DVER_H_
#define _DVER_H_

#define VERSION "2.2.0"
#define VER1 2
#define VER2 2
#define VER3 0
int dver_val[7]={0,2,2,0};
int verval(int idx){
	return dver_val[idx];
}
string version(){
	return stringf("%d.%d.%d",verval(1),verval(2),verval(3));
}
string longversion(){
	return stringf("DevGUI v%s",version().c_str());
}

#endif

