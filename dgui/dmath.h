#ifndef _DGUI_DMATH_H_
#define _DGUI_DMAIN_H_

#define PI 3.14159265358979323846
#define EE 2.718281828459

char hexN[17]={"0123456789ABCDEF"};
char hexn[17]={"0123456789abcdef"};
int imax(int _,int __){
	return _>__?_:__;
}
int imin(int _,int __){
	return _<__?_:__;
}
int iabs(int _){
	return _>0?_:(-_);
}
int dround(double x){
	return (int)(x+0.5); 
}
int ceildiv(int a,int b){
	return (a+b-1)/b;
}
int floordiv(int a,int b){
	return a/b;
}
double DegToArc(double deg){
	return deg/180.0*PI;
}
double ArcToDeg(double arc){
	return arc/PI*180.0;
}
double dsin(double deg){
	return sin(DegToArc(deg));
}
double dcos(double deg){
	return cos(DegToArc(deg));
}
double dtan(double deg){
	return tan(DegToArc(deg));
}
double dasin(double v){
	return ArcToDeg(asin(v));
}
double dacos(double v){
	return ArcToDeg(acos(v));
}
double datan(double v){
	return ArcToDeg(atan(v));
}
int HexNum(char c){
	if(c>='0'&&c<='9'){
		return c-48;
	}
	if(c>='A'&&c<='F'){
		return c-55;
	}
	if(c>='a'&&c<='f'){
		return c-87;
	}
	return 0;
}
int HexToDec255(string hx){
	return HexNum(hx[0])<<4|HexNum(hx[1]);
}
string DecToHex255(int dc){
	return ESTR+hexn[dc>>4]+hexn[dc&15];
}
string DecToHeX255(int dc){
	return ESTR+hexN[dc>>4]+hexN[dc&15];
}
bool AinB(DPOINT a,DRECT b){
	return(
		a.x>=b.x1&&a.x<=b.x2&&
		a.y>=b.y1&&a.y<=b.y2
	);
}
bool inrect(DPOINT a,DRECT b){
	return AinB(a,b);
} 
#endif
