#ifndef _DGUI_DDEF_H_
#define _DGUI_DDEF_H_

#define UNUSED_VAR(var) ((void)var)
#define UNUSED UNUSED_VAR

#define makePRFunId(name) ____DevGUI___Pre_Run____dgui_temp_vars_functions__the_name_is__##name##_____this_is_part_of_an_initializer_______DGUI___DO_NOT_USE_THIS_NAME___0_____
#define makePRVarId(name) ____DevGUI___Pre_Run____dgui_temp_vars_variables__the_name_is__##name##_____this_is_part_of_an_initializer_______DGUI___DO_NOT_USE_THIS_NAME___0_____
#define pre_run(name,fun) char makePRFunId(name)(){fun;return 0;}char makePRVarId(name)=makePRFunId(name)()

#ifdef DGUI_PROJECT
	#define _DevGUI_main_ __DevGUI__UserMainFunction__0__DO_NOT_USE_THIS_NAME__0__
	#define dgmain_b _DevGUI_main_
	#define dgmain dgui_ns::dgmain_b
	#define main dgmain	
#endif

#define DGUI_TRANSPEN NULL_PEN
#define DGUI_TRANSBRUSH NULL_BRUSH

#define DSW_SHOW SW_SHOW
#define DSW_HIDE SW_HIDE
#define DSW_MIN SW_MINIMIZE
#define DSW_MAX SW_MAXIMIZE

#define WM_DGUI_UPDATE ((WM_USER)+666)

#define CMD_POLY 1
#define CMD_ELLIPSE 2
#define CMD_TEXT 3

#define STRLENMX 100007

#define COLNAME_HEX '#'

#define PNTYPE_TRANSPARENT 0
#define PNTYPE_SOLID 1
#define PNTYPE_DASH 2
#define PNTYPE_DOT 3

#define MAXW 3000
#define MAXH 3000

typedef unsigned uint,unt;

typedef const int &cir;
typedef const string &csr;

typedef void *ANYTYPE;

typedef class _DPOINT{
	public:
		int x,y;
		_DPOINT(){}
		_DPOINT(cir _x,cir _y):
			x(_x),y(_y){}
		inline bool operator<(const _DPOINT &dpb)const{
			if(y==dpb.y){
				return x<dpb.x;
			}
			return y<dpb.y;
		}
		inline bool operator>(const _DPOINT &dpb)const{
			return dpb<(*this);
		}
		inline bool operator==(const _DPOINT &dpb)const{
			return x==dpb.x&&y==dpb.y;
		}
}DPOINT,*PDPOINT,&RDPOINT;
POINT toPOINT(DPOINT p){
	POINT r;
	r.x=p.x;
	r.y=p.y;
	return r;
}
POINT toSysPoint(DPOINT p){
	return toPOINT(p);
}
typedef class _DRECT{
	public:
		int x1,y1,x2,y2;
		_DRECT(){}
		_DRECT(cir _x1,cir _y1,cir _x2,cir _y2):
			x1(_x1),y1(_y1),x2(_x2),y2(_y2){}
		_DRECT(const RDPOINT p1,const RDPOINT p2):
			x1(p1.x),y1(p1.y),x2(p2.x),y2(p2.y){} 
}DRECT,*PDRECT,&RDRECT;

typedef unsigned DGPCMDTYPE;
typedef void *DGPPARAM;
/*class DGPPDOT{
	public:
		int x,y,r;
};*/
typedef PDPOINT DPOINTS;
class DGPPPOLY{
	public:
		int len;
		DPOINTS pnts;
		DGPPPOLY(){} 
};
class DGPPELL{
	public:
		int x,y,r1,r2;
};
class DGPPTXT{
	public:
		int x,y;
		string txt;
};

class DGPCMD{
	public:
		DGPCMDTYPE type;
		DGPPARAM param;
		DGPCMD(){}
		DGPCMD(const DGPCMDTYPE &_t,DGPPARAM _p):
			type(_t),param(_p){}
};

struct FILEFILTER{
	string info,expr;
	FILEFILTER(){}
	FILEFILTER(csr _i,csr _e):
		info(_i),expr(_e){} 
};

typedef FILEFILTER FFILTER,*PFILEFILTER,*PFFILTER;
typedef const PFFILTER FILEFILTERS,FFILTERS;

typedef PAINTSTRUCT PST;

typedef RECT DGBPRECT;
typedef COLORREF DCOLOR,DCOL;
typedef SIZE DSIZE;

const int DefWndWidth=640;
const int DefWndHeight=480;
const int DefWndX=150;
const int DefWndY=150;
const string DefWndTitle="ÎÞ±êÌâ";
const DCOLOR defbkcol=RGB(255,255,255);
const DCOLOR defpncol=RGB(80,80,80);
const DCOLOR defflcol=RGB(153,255,255);
const DCOLOR defpnwgt=1;
const DCOLOR defpntype=PNTYPE_SOLID;
const string deffname="Î¢ÈíÑÅºÚ";
int deffcol=RGB(0,0,0),deffwth=15,deffhgt=40,deffwgt=400;

const string ESTR="";

template <typename T>
T transany(ANYTYPE at){
	return (T)((long long)(at));
}

#ifdef DGUI_PROJECT
int dgmain_b(void);
#endif

#endif
