#ifndef _DGUI_DUSER_H_
#define _DGUI_DUSER_H_

map<string,COLORREF> cols;

DCOLOR getRGB(int r,int g,int b){
	return RGB(r,g,b);
}
int getR(DCOLOR col){
	return (col&0xff);
}
int getG(DCOLOR col){
	return (col&0xff00)>>8;
}
int getB(DCOLOR col){
	return (col&0xff0000)>>16;
}
int getcolex(DCOLOR col){
	return (col&0xff000000)>>16;
}
void addcolname(string nam,DCOLOR dc){
	cols[trimx(nam)]=dc;
}
void initcols(void){
	addcolname("aqua",getRGB(0,255,255));
	addcolname("black",getRGB(0,0,0));
	addcolname("blue",getRGB(0,0,255));
	addcolname("brown",getRGB(185,122,87));
	addcolname("crimson",getRGB(220,20,60));
	addcolname("cyan",getRGB(0,255,255));
	addcolname("default",defflcol);
	addcolname("green",getRGB(0,128,0));
	addcolname("grey",getRGB(128,128,128));
	addcolname("lime",getRGB(0,255,0));
	addcolname("orange",getRGB(255,165,0));
	addcolname("purple",getRGB(128,0,255));
	addcolname("pink",getRGB(255,192,203));
	addcolname("pink",getRGB(255,192,203));
	addcolname("red",getRGB(255,0,0));
	addcolname("teal",getRGB(0,128,128));
	addcolname("violet",getRGB(238,130,238));
	addcolname("wheat",getRGB(245,222,179));
	addcolname("white",getRGB(255,255,255));
	addcolname("yellow",getRGB(255,255,0));
	addcolname("sky",getRGB(128,255,255));
	//cols["dark purple"]=RGB(128,0,128);
	//cols["sky blue"]=RGB(128,255,255);
}
void init_duser(){
	initcols();
}
template <typename T>
void dswap(T &a,T &b){
	T tmp=a;
	a=b;
	b=tmp; 
}
void setup(int x,int y,int w,int h,string title){
	syncevent("Setup",NULL);
	//MessageBox(NULL,"SETUP","",0);
	#ifndef DGUI_PROJECT
	CallWinMain();
	#endif
	//cprintf("SETUP %d %d %d %d %s\n",x,y,w,h,title.c_str());
	//Sleep(80);
	while((!g_hdc)||(!g_hwnd));
	settitle(title);
	movewindow(x,y,w,h);
	movewindow(x,y,w,h);
	movewindow(x,y,w,h);
	showwindow();
}
void setup(int x,int y,int w,int h){
	setup(x,y,w,h,DefWndTitle);
}
void setup(int w,int h,string title){
	setup(DefWndX,DefWndY,w,h,title);
}
void setup(int w,int h){
	setup(DefWndX,DefWndY,w,h,DefWndTitle);
}
void setup(string title){
	//ConsoleOut("SUS\n");
	setup(DefWndX,DefWndY,DefWndWidth,DefWndHeight,title);
}
void setup(void){
	setup(DefWndX,DefWndY,DefWndWidth,DefWndHeight,DefWndTitle);
}

void ellipse(int x,int y,int r1,int r2){
	DGPPELL *tmp=new DGPPELL;
	tmp->x=x,
	tmp->y=y,
	tmp->r1=r1,
	tmp->r2=r2;
	//pushcmd(CMD_ELLIPSE,tmp);
	calldgbp(dgbp_ellipse(*tmp));
	delete tmp;
}
void polygon(int len,DPOINTS pnts){
	DGPPPOLY *tmp=new DGPPPOLY;
	tmp->len=len;
	tmp->pnts=new DPOINT[len+3];
	for(int i=0;i<len;++i){
		tmp->pnts[i]=pnts[i];
	}
	calldgbp(dgbp_poly(*tmp));
	delete tmp->pnts;
	delete tmp;
}
void systextout(int x,int y,string txt){
	DGPPTXT *tmp=new DGPPTXT;
	tmp->x=x;
	tmp->y=y;
	tmp->txt=txt;
	calldgbp(dgbp_text(*tmp));
	ellipse(0,0,0,0);
	delete tmp;
}
void textout(int x,int y,string txt){
	string t="";
	int cy=y;
	int l=txt.size();
	for(int i=0;i<l;++i){
		switch(txt[i]){
			case '\n':{
				systextout(x,cy,t);
				t="";
				cy+=fth+0;
				break;
			}
			default:{
				t+=txt[i];
				break;
			} 
		}
	}
	systextout(x,cy,t);
}
DSIZE stringoutlen(string str){
	SIZE sz;
	GetTextExtentPoint32(g_hdc,str.c_str(),str.size(),&sz);
	return sz;
}

void vppoly(int len,va_list vl){
	DPOINT *p=new DPOINT[len+3];
	for(int i=0;i<len;++i){
		p[i]=va_arg(vl,DPOINT);
	}
	polygon(len,p);
	delete[] p;
	va_end(vl);
}
void vpoly(int len,va_list vl){
	DPOINT *p=new DPOINT[len+3];
	for(int i=0;i<len;++i){
		int x=va_arg(vl,int);
		int y=va_arg(vl,int);
		p[i]=DPOINT(x,y);
	}
	polygon(len,p);
	delete[] p;
	va_end(vl);
}
void ppoly(int len,...){
	va_list vl;
	va_start(vl,len);
	vppoly(len,vl);
}
void poly(int len,...){
	va_list vl;
	va_start(vl,len);
	vpoly(len,vl);
}
void rectangle(DPOINT p1,DPOINT p2){
	int x1=p1.x,y1=p1.y,x2=p2.x,y2=p2.y;
	poly(4,x1,y1,x2,y1,x2,y2,x1,y2);
}
void rectangle(int x,int y,int a,int b){
	rectangle(DPOINT(x,y),DPOINT(x+a,y+b));
}
void square(int x,int y,int a){
	rectangle(x,y,a,a);
}
void circle(int x,int y,int r){
	ellipse(x,y,r,r);
}
void vtextoutf(int x,int y,string fmt,va_list vl){
	char out[5007]={""};
	vsprintf(out,fmt.c_str(),vl);
	textout(x,y,out);
}
void textoutf(int x,int y,string fmt,...){
	va_list vl;
	va_start(vl,fmt);
	vtextoutf(x,y,fmt,vl);
}
void setfont(string name,int w,int h,int weight,bool ita,bool und,bool del){
	HFONT hf=CreateFont(h,w,0,0,weight,ita,und,del,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH||FF_DONTCARE,name.c_str());
	SelectObject(g_hdc,hf);
	DeleteObject(g_hf);
	g_hf=hf;
	ftw=w;
	fth=h;
	ftwt=weight;
	fntname=name;
	fti=ita;
	ftu=und;
	ftd=del;
}
void setfontname(string name){
	setfont(name,ftw,fth,ftw,fti,ftu,ftd);
}
void clear(){
	RECT rct;
	GetClientRect(g_hwnd,&rct);
	calldgbp(dgbp_clear(rct));
}

bool keydown(int key){
	return GetAsyncKeyState(key)&0x8000;
}
DPOINT mousepos(void){
	POINT t;
	GetCursorPos(&t);
	ScreenToClient(g_hwnd,&t);
	DPOINT ret=DPOINT(t.x,t.y);
	return ret;
}
DCOLOR getpxcol(int x,int y){
	return (DCOLOR)GetPixel(g_hdc,x,y);
}
void setpxcol(int x,int y,DCOLOR col){
	SetPixel(g_hdc,x,y,col);
	SetPixel(g_hdc,x,y,col);
	SetPixel(g_hdc,x,y,col);
	SetPixel(g_hdc,x,y,col);
	SetPixel(g_hdc,x,y,col);
	SetPixel(g_hdc,x,y,col);
}
DCOLOR getcolor(string colname){
	string _="";
	int r,g,b;
	if(colname[0]=='#'){
		unsigned sz=colname.size();
		if(sz==1) return bkcol;
		if(sz<7){
			r=HexToDec255(_+colname[1]+"0"),
			g=HexToDec255(_+colname[2]+"0"),
			b=HexToDec255(_+colname[3]+"0");
			return getRGB(r,g,b);
		}
		r=HexToDec255(_+colname[1]+colname[2]),
		g=HexToDec255(_+colname[3]+colname[4]),
		b=HexToDec255(_+colname[5]+colname[6]);
		return getRGB(r,g,b);
	}
	return cols[trimx(colname)];
}
DCOLOR makecolor(string colname){
	return getcolor(colname);
} 
void setpen(int type,DCOLOR col,int wgt){
	pncol=col,
	pnwgt=wgt,
	pntype=type;
	DeleteObject(g_hpn);
	g_hpn=CreatePen(winpnstyle(pntype),pnwgt,pncol);
	SelectObject(g_hdc,g_hpn);
}
void setpentype(int type){
	setpen(type,pncol,pnwgt);
}
void setpencolor(DCOLOR col){
	setpen(pntype,col,pnwgt);
}
void setpenwidth(int wgt){
	setpen(pntype,pncol,wgt);
}
void setfillcolor(DCOLOR col){
	brcol=col;
	DeleteObject(g_hbr);
	g_hbr=CreateSolidBrush(brcol);
	SelectObject(g_hdc,g_hbr);
}
int colordif(DCOLOR a,DCOLOR b){
	return (
		iabs(getR(a)-getR(b))+
		iabs(getG(a)-getG(b))+
		iabs(getB(a)-getB(b))
	)*100/3;
}
void fillarea(int x,int y,int tolerance=0){
	static int vst[MAXW][MAXH];
	static int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
	queue<DPOINT> q;
	DPOINT tmp;
	DCOLOR origin=getpxcol(x,y);
	int tx,ty;
	memset(vst,0,sizeof vst);
	stopupdate();
	q.push(DPOINT(x,y));
	setpxcol(x,y,brcol);
	vst[x][y]=1;
	while(!q.empty()){
		tmp=q.front();
		q.pop();
		for(int i=0;i<4;++i){
			tx=tmp.x+dir[i][0],
			ty=tmp.y+dir[i][1];
			if(tx<0||tx>wndw||ty<0||ty>wndh){
				continue;
			}
			if(vst[tx][ty]||colordif(origin,getpxcol(tx,ty))>tolerance){
				continue;
			}
			setpxcol(tx,ty,brcol);
			q.push(DPOINT(tx,ty));
			vst[tx][ty]=1;
		}
	}
	continueupdate();
}

long long winfo(string key){
	RECT wndr,clntr;
	GetWindowRect(g_hwnd,&wndr);
	GetClientRect(g_hwnd,&clntr);
	if(key=="x"){
		return wndr.left;
	}
	if(key=="y"){
		return wndr.top;
	}
	if(key=="window-x"){
		return wndr.left;
	}
	if(key=="window-y"){
		return wndr.top;
	}
	if(key=="client-x"){
		POINT clnt={clntr.left,clntr.top};
		ClientToScreen(g_hwnd,&clnt);
		return clnt.x;
	}
	if(key=="client-y"){
		POINT clnt={clntr.left,clntr.top};
		ClientToScreen(g_hwnd,&clnt);
		return clnt.y;
	}
	if(key=="width"){
		return clntr.right;
	}
	if(key=="height"){
		return clntr.bottom;
	}
	return -1;
}
void nullfun(){}
void sleep(int ms){
	Sleep(ms);
}
string filedialog(bool save,int typecnt,string title,FILEFILTERS flt,bool fltinfo,bool mult,bool hid){
	OPENFILENAME ofn;
	char s[1007],*buf=new char[MAX_PATH+3];
	int sl;
	string ret;
	memset(&ofn,0,sizeof ofn);
	buf[0]=0;
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=g_hwnd;
	ofn.lpstrFile=buf;
	ofn.nMaxFile=MAX_PATH;
	ofn.Flags=OFN_EXPLORER|OFN_HIDEREADONLY;
	ofn.lpstrTitle=title.c_str();
	if(save){
		ofn.Flags|=(OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT);
	}
	else{
		ofn.Flags|=OFN_FILEMUSTEXIST;
	}
	if(mult){
		ofn.Flags|=OFN_ALLOWMULTISELECT;
	}
	if(hid){
		ofn.Flags|=OFN_FORCESHOWHIDDEN;
	} 
	sl=-1;
	for(int i=0;i<typecnt;++i){
		string t1=flt[i].info,t2=flt[i].expr;
		if(fltinfo){
			t1+=ESTR+" ("+t2+')';
		}
		for(unt j=0;j<t1.size();++j){
			s[++sl]=t1[j];
		}
		s[++sl]=0;
		for(unt j=0;j<t2.size();++j){
			s[++sl]=t2[j];
		}
		s[++sl]=0;
	}
	s[++sl]=0;
	ofn.lpstrFilter=s;
	//puts(lenstr(s,sl+1).c_str());
	if(save){
		GetSaveFileName(&ofn);
	}
	else{
		GetOpenFileName(&ofn);
	}
	ret=string(buf);
	delete[] buf;
	return ret;
}
string dirdialog(){
	BROWSEINFO bi;
	memset(&bi,0,sizeof bi);
	LPMALLOC mal;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	char *s=new char[MAX_PATH+3];
	string ret;
	if(idl){
		SHGetPathFromIDList(idl,s);
		if(SUCCEEDED(SHGetMalloc(&mal))){
			mal->Free(idl);
			mal->Release();
		}
		ret=string(s);
	}
	else{
		ret="";
	}
	delete[] s;
	return ret;
}
//int initer=init_duser();
pre_run(init_duser,init_duser(););

#endif
