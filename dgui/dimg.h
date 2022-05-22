#ifndef _DIMG_H_
#define _DIMG_H_

typedef class DGUIPIC{
	public:
		int w,h;
		HBITMAP hbm;
		DGUIPIC(){}
		bool valid()const{
			return hbm!=NULL;
		} 
		void del(){
			if(valid()){
				DeleteObject(hbm);
				hbm=NULL;
			}
		}
		~DGUIPIC(){
			del();
		}
}IMAGE,PICTURE,BMP;

void loadbmp(BMP &buf,string path,int w,int h){
	buf.del();
	//buf.path=path;
	buf.w=w;
	buf.h=h;
	buf.hbm=(HBITMAP)LoadImage(NULL,path.c_str(),IMAGE_BITMAP,w,h,LR_LOADFROMFILE);
}
int getbcnt(int x){
	if(x<=1) return 1;
	if(x<=4) return 4;
	if(x<=8) return 8;
	return 24;
}
bool savebmp(const BMP &bmp,string path){
	if(!bmp.valid()){
		return 0;
	}
	HDC hdc;
	WORD bcnt;
	DWORD palsize=0,bitsize,dibsize,wtn;
	BITMAP bm;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	LPBITMAPINFOHEADER pbm;
	HANDLE hdib,hpal,hpalo=NULL;
	HANDLE ofl;
	
	hdc=CreateDC("DISPLAY",NULL,NULL,NULL);
	bcnt=(WORD)getbcnt(GetDeviceCaps(hdc,PLANES)*GetDeviceCaps(hdc,BITSPIXEL));
	GetObject(bmp.hbm,sizeof(bm),&bm);
	bih.biSize=sizeof(BITMAPINFOHEADER);
	bih.biWidth=bm.bmWidth;
	bih.biHeight=bm.bmHeight;
	bih.biPlanes=1;
	bih.biBitCount=bcnt;
	bih.biCompression=BI_RGB;
	bih.biSizeImage=0;
	bih.biXPelsPerMeter=0;
	bih.biYPelsPerMeter=0;
	bih.biClrImportant=0;
	bih.biClrUsed=0;
	DeleteDC(hdc);
	
	bitsize=(ceildiv(bm.bmWidth*(int)(bcnt)*bm.bmHeight,32)<<2);
	hdib=GlobalAlloc(GHND,bitsize+palsize+sizeof(BITMAPINFOHEADER));
	pbm=(LPBITMAPINFOHEADER)GlobalLock(hdib);
	*pbm=bih;
	hpal=GetStockObject(DEFAULT_PALETTE);
	if(hpal){
		hdc=GetDC(NULL);
		hpalo=SelectPalette(hdc,(HPALETTE)hpal,0);
		RealizePalette(hdc);
	}
	
	GetDIBits(hdc,bmp.hbm,0,(UINT)bm.bmHeight,(LPSTR)(pbm)+sizeof(BITMAPINFOHEADER)+palsize,(LPBITMAPINFO)pbm,DIB_RGB_COLORS);
	if(hpalo){
		SelectPalette(hdc,(HPALETTE)hpalo,1);
		RealizePalette(hdc);
		ReleaseDC(NULL,hdc);
	}
	
	ofl=CreateFile(path.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(ofl==INVALID_HANDLE_VALUE){
		return 0;
	}
	dibsize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+palsize+bitsize;
	bfh.bfType=0x4d42;
	bfh.bfSize=dibsize;
	bfh.bfReserved1=0;
	bfh.bfReserved2=0;
	bfh.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+palsize;
	
	WriteFile(ofl,(LPCSTR)(&bfh),sizeof(BITMAPFILEHEADER),&wtn,NULL);
	WriteFile(ofl,(LPCSTR)(pbm),dibsize,&wtn,NULL);
	
	GlobalUnlock(hdib);
	GlobalFree(hdib);
	CloseHandle(ofl);
	return 1;
}
void drawbmp(const BMP &bmp,int x,int y){
	HDC thdc=CreateCompatibleDC(g_hdc);
	SelectObject(thdc,bmp.hbm);
	BitBlt(g_hdc,x,y,bmp.w,bmp.h,thdc,0,0,SRCCOPY);
	DeleteDC(thdc);
}
void drawbmppara(const BMP &bmp,DPOINT p1,DPOINT p2,DPOINT p3){
	HDC thdc=CreateCompatibleDC(g_hdc);
	POINT *pnts=new POINT[4];
	pnts[0]=toPOINT(p1);
	pnts[1]=toPOINT(p2);
	pnts[2]=toPOINT(p3);
	SelectObject(thdc,bmp.hbm);
	PlgBlt(g_hdc,pnts,thdc,0,0,bmp.w,bmp.h,NULL,0,0);
	delete[] pnts;
	DeleteDC(thdc);
}
void drawbmprotate(const BMP &bmp,int x,int y,int deg){
	long double x0,y0,deg0,len;
	DPOINT p1,p2,p3;
	if(deg<0){
		deg+=ceildiv(-deg,360);
	}
	deg%=360;
	deg=360-deg;
	x0=1.0*x+(bmp.w/2.0);
	y0=1.0*y+(bmp.h/2.0);
	deg0=datan(1.0*bmp.h/bmp.w);
	len=sqrt(bmp.w*bmp.w+bmp.h*bmp.h)/2.0;
	p1=DPOINT(x0-len*dcos(deg0-deg),y0-len*dsin(deg0-deg));
	p2=DPOINT(x0+len*dcos(deg0+deg),y0-len*dsin(deg0+deg));
	p3=DPOINT(x0-len*dcos(deg0+deg),y0+len*dsin(deg0+deg));
	drawbmppara(bmp,p1,p2,p3);
}//Magic and Confusing
void drawbmpscale(const BMP &bmp,int x,int y,int w,int h){
	HDC thdc=CreateCompatibleDC(g_hdc);
	SelectObject(thdc,bmp.hbm);
	StretchBlt(g_hdc,x,y,w,h,thdc,0,0,bmp.w,bmp.h,SRCCOPY);
	DeleteDC(thdc);
}
void drawbmpmirrorx(const BMP &bmp,int x,int y){
	DPOINT p1,p2,p3;
	p1=DPOINT(x+bmp.w,y);
	p2=DPOINT(x,y);
	p3=DPOINT(x+bmp.w,y+bmp.h);
	drawbmppara(bmp,p1,p2,p3);
}
void drawbmpmirrory(const BMP &bmp,int x,int y){
	DPOINT p1,p2,p3;
	p1=DPOINT(x,y+bmp.h);
	p2=DPOINT(x+bmp.w,y+bmp.h);
	p3=DPOINT(x,y);
	drawbmppara(bmp,p1,p2,p3);
}
void windowbmp(BMP &buf,int x,int y,int w,int h){
	buf.del();
	HDC hdcmem;
	HBITMAP hbmem,hbold,hbret;
	hdcmem=CreateCompatibleDC(g_hdc);
	hbmem=CreateCompatibleBitmap(g_hdc,w,h);
	hbold=(HBITMAP)SelectObject(hdcmem,hbmem);
	BitBlt(hdcmem,0,0,w,h,g_hdc,x,y,SRCCOPY);
	hbret=(HBITMAP)SelectObject(hdcmem,hbold);
	DeleteDC(hdcmem);
	//DeleteObject(hbmem)
	DeleteObject(hbold);
	buf.w=w,
	buf.h=h,
	buf.hbm=hbret;
}

#endif
