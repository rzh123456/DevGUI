#ifndef _DGUI_DBASIC_H_
#define _DGUI_DBASIC_H_

HINSTANCE g_hInst;
volatile HWND g_hwnd;
/*!!!*/

bool wflg;

HANDLE hMainThread,hTimerThread;
int wndx,wndy;
int wndw,wndh;
int dcw,dch;
int timerInterv=100,autoupd=1;

int pnstyles[107]={PS_NULL,PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,PS_INSIDEFRAME,PS_USERSTYLE,PS_ALTERNATE,PS_STYLE_MASK};

volatile HDC g_hdc;
volatile HBITMAP g_hbm;
volatile HPEN g_hpn;
volatile HBRUSH g_hbr;
volatile HFONT g_hf;

DCOLOR bkcol=defbkcol;
DCOLOR pncol=defpncol,brcol=defflcol,ftcol=deffcol;
int pnwgt=defpnwgt,pntype=defpntype;
int ftw=deffwth,fth=deffhgt,ftwt=deffwgt;
bool fti=0,ftu=0,ftd=0;
string fntname=deffname; 

#define calldgbp(cmd) if(1){if(g_hdc==NULL){SendMessage(g_hwnd,WM_PAINT,0,0);}else{cmd;}}

class DGUIOptions{
	public:
		DCOLOR pncol,brcol;
		int pnwgt;
		int fwth,fhgt,fwgt;
}g_opt;

int winpnstyle(int dgpntype){
	return pnstyles[dgpntype];
}

#ifdef DGUI_PROJECT
unsigned __stdcall CallDGUIMainThread(void *dgmpara){
	UNUSED(dgmpara);
	dgmain_b();
	return 0;
}
#endif
unsigned __stdcall DGUITimerThread(void *dgtpara){
	RECT rct;
	UNUSED(dgtpara);
	while(1){
		Sleep(timerInterv);
		//SendMessage(g_hwnd,WM_DGUI_UPDATE,0,0);
		if(autoupd){ 
			GetClientRect(g_hwnd,&rct);
			InvalidateRect(g_hwnd,&rct,1);
			SendMessage(g_hwnd,WM_PAINT,0,0);
		} 
	}
	return 0;
}
void StartDGUITimer(){
	unsigned threadID;
	hTimerThread=(HANDLE)_beginthreadex(NULL,0,&DGUITimerThread,NULL,0,&threadID);
}
#ifdef DGUI_PROJECT
void CallDGUIMain(){
	unsigned threadID;
	hMainThread=(HANDLE)_beginthreadex(NULL,0,&CallDGUIMainThread,NULL,0,&threadID);
}
#endif

bool fileexist(string path){
	DWORD fa=GetFileAttributes(path.c_str());
	if(fa==INVALID_FILE_ATTRIBUTES||(fa&FILE_ATTRIBUTE_DIRECTORY)){
		return 0;
	}
	return 1;
}
void deletefile(string path){
	DeleteFile(path.c_str());
}
void delfile(string path){
	deletefile(path);
}
void renamefile(string path,string newname){
	rename(path.c_str(),newname.c_str());
}

POINT makePOINT(int xx,int yy){
	POINT ret;
	ret.x=xx,
	ret.y=yy;
	return ret;
}

/*DGBP functions*/
void dgbp_poly(DGPPPOLY para){
	int len=para.len;
	POINT *pnts=new POINT[len+3];
	for(int i=0;i<len;++i){
		pnts[i]=makePOINT(para.pnts[i].x,para.pnts[i].y); 
	}
	Polygon(g_hdc,pnts,len);
	delete[] pnts;
	//delete[] para.pnts;
}
void dgbp_pline(DGPPPOLY para){
	int len=para.len;
	POINT *pnts=new POINT[len+3];
	for(int i=0;i<len;++i){
		pnts[i]=makePOINT(para.pnts[i].x,para.pnts[i].y); 
	}
	Polyline(g_hdc,pnts,len);
	delete[] pnts;
}
void dgbp_ellipse(DGPPELL para){
	//ConsoleOut("ELLIPSE\n");
	//cprintf("%d %d %d %d\n",para.x,para.y,para.r1,para.r2);
	Ellipse(g_hdc,para.x-para.r1,para.y-para.r2,para.x+para.r1,para.y+para.r2);
}
void dgbp_text(DGPPTXT para){
	TextOut(g_hdc,para.x,para.y,para.txt.c_str(),para.txt.size());
}
void dgbp_clear(DGBPRECT rct){
	HBRUSH hbrBk=CreateSolidBrush(bkcol);
	//cprintf("hbrBk=%llu\n",(long long unsigned)(hbrBk)); 
	/*int ret=*/
	FillRect(g_hdc,&rct,hbrBk);
	//cprintf("fr=%d\n",ret); 
	DeleteObject(hbrBk);
}

void init_paint(HDC hdcScr,RECT rct){
	g_hdc=CreateCompatibleDC(hdcScr);
	g_hbm=CreateCompatibleBitmap(hdcScr,rct.right,rct.bottom);
	g_hpn=CreatePen(winpnstyle(pntype),pnwgt,pncol);
	g_hbr=CreateSolidBrush(brcol);
	g_hf=CreateFont(deffhgt,deffwth,0,0,deffwgt,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH||FF_DONTCARE,"Î¢ÈíÑÅºÚ");
	//cprintf("ghbm=%llu\n",(long long unsigned)(g_hbm));
	SelectObject(g_hdc,g_hbm);
	SelectObject(g_hdc,g_hpn); 
	SelectObject(g_hdc,g_hbr);
	SelectObject(g_hdc,g_hf);
	SetBkMode(g_hdc,TRANSPARENT);
	dgbp_clear(rct);
	/*
		Here!I am elem[51],I made the previous 2 lines reversed and debugged for 2 days.
		Duck Hunt!!!
	*/
}

LRESULT CALLBACK DevGUIWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam){
	switch(Message){
		case WM_CREATE:{
			//printf("ERR:%d\n",GetLastError());
			wflg=1;
			//OpenConsole();
			//ConsoleOut("Console Opened!\n");
			Sleep(10);
			SendMessage(hwnd,WM_PAINT,0,0);
			StartDGUITimer();
			#ifdef DGUI_PROJECT
			CallDGUIMain();
			#endif
			asyncevent("Create",NULL);
			break;
		}
		case WM_PAINT:{
			//printf("ERR:%d\n",GetLastError());
			PST pst;
			RECT rct;
			GetClientRect(hwnd,&rct);
			BeginPaint(hwnd,&pst);
			HDC hdcScr=GetDC(hwnd);
			if(g_hdc==NULL){
				init_paint(hdcScr,rct);
			}
			//dgupdate();
			BitBlt(hdcScr,0,0,rct.right,rct.bottom,g_hdc,0,0,SRCCOPY);
			ReleaseDC(hwnd,hdcScr);
			EndPaint(hwnd,&pst);
			/*if(g_hdc==NULL){
				break;
			}*/
			//MessageBox(NULL,"UPDATE","DevGUI",0);
			break;
		}
		case WM_LBUTTONDOWN:{
			asyncevent("MouseDown-L",NULL);
			break;
		}
		case WM_RBUTTONDOWN:{
			asyncevent("MouseDown-R",NULL);
			break;
		}
		case WM_MBUTTONDOWN:{
			asyncevent("MouseDown-M",NULL);
			break;
		}
		case WM_LBUTTONUP:{
			asyncevent("MouseUp-L",NULL);
			break;
		}
		case WM_RBUTTONUP:{
			asyncevent("MouseUp-R",NULL);
			break;
		}
		case WM_MBUTTONUP:{
			asyncevent("MouseUp-M",NULL);
			break;
		}
		case WM_SYSKEYDOWN:{
			asyncevent("KeyDown",(EPARA)wParam);
			CallWindowProc(DefWindowProc,hwnd,Message,wParam,lParam);
			break;
		}
		case WM_KEYDOWN:{
			asyncevent("KeyDown",(EPARA)wParam);
			break;
		}
		case WM_COMMAND:{
			int id=LOWORD(wParam);
			asyncevent(stringf("Button-%d",id),NULL);
			asyncevent("Button",(EPARA)(long long)id);
			break;
		}
		case WM_CHAR:{
			asyncevent("CharKeyDown",(EPARA)wParam);
			break;
		}
		case WM_SIZE:{
			DRECT x=DRECT(0,0,LOWORD(lParam),HIWORD(lParam)); 
			asyncevent("Size",&x);
			break;
		}
		case WM_SIZING:{
			LPRECT r=(LPRECT)(lParam);
			DRECT x=DRECT(0,0,r->right,r->bottom);
			syncevent("Sizing",&x);
			Sleep(10);
			r->right=x.x2;
			r->bottom=x.y2;
			break;
		}
		case WM_MOVE:{
			asyncevent("Move",NULL);
			break;
		}
		case WM_MOVING:{
			LPRECT r=(LPRECT)(lParam);
			DRECT x=DRECT(r->left,r->top,r->right,r->bottom);
			syncevent("Moving",&x);
			Sleep(10);
			r->left=x.x1;
			r->top=x.y1;
			r->right=x.x2;
			r->bottom=x.y2;
			break;
		}
		case WM_CLOSE:{
			int *retp=new int;
			int ret;
			*retp=1;
			asyncevent("Close",NULL);
			syncevent("Closing",(EPARA)retp);
			ret=*retp;
			delete retp;
			if(ret){
				SendMessage(hwnd,WM_DESTROY,0,0);
			}
			break;
		}
		case WM_DESTROY:{
			asyncevent("AsyncDestroy",NULL);
			syncevent("Destroy",NULL);
			DeleteObject(g_hpn);
			DeleteObject(g_hbr);
			DeleteObject(g_hbm);
			DeleteDC(g_hdc);
			CloseHandle(hMainThread);
			CloseHandle(hTimerThread); 
			wflg=0;
			//printf("wflg=%d\n",wflg);
			PostQuitMessage(0);
			break;
		}
		default:
			return CallWindowProc(DefWindowProc,hwnd,Message,wParam,lParam);
	}
	return 0;
}
int CreateDGUIWin(){
	//MessageBox(NULL,"cdgw","",0);
	WNDCLASSEX wc;
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = DevGUIWndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = g_hInst;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = "DevGUIWindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	if(!RegisterClassEx(&wc)){
		MessageBox(NULL,"´°¿Ú×¢²á´íÎó!","´íÎó",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	g_hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,"DevGUIWindowClass","ÎÞ±êÌâ",/*WS_VISIBLE|*/WS_OVERLAPPEDWINDOW,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN)+100,
		GetSystemMetrics(SM_CYSCREEN)+100,
		NULL,NULL,g_hInst,NULL);
	//printf("NOW G_HW=%lld\n",g_hwnd);
	wndw=DefWndWidth;
	wndh=DefWndHeight;
	if(g_hwnd==NULL){
		MessageBox(NULL,"´°¿Ú´´½¨´íÎó!","´íÎó",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	//MessageBox(NULL,"Create OK","",0);
	return 1;
}
int WINAPI dgWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	MSG Msg;

	UNUSED(hPrevInstance);
	UNUSED(lpCmdLine);
	UNUSED(nCmdShow);
	
	g_hInst=hInstance;
	//MessageBox(NULL,"dgwm","",0);
	if(!CreateDGUIWin()){
		//MessageBox(NULL,"ERR0","",0);
		return 0;
	}
	while(GetMessage(&Msg,NULL,0,0)>0){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

#ifndef DGUI_PROJECT
unsigned __stdcall dgWinThread(void *para){
	UNUSED(para);
	dgWinMain(NULL,NULL,NULL,0);
	return 0;
}
void CallWinMain(){
	unsigned threadID;
	_beginthreadex(NULL,0,&dgWinThread,NULL,0,&threadID);
}
#endif

void settitle(string wndtitle){
	SetWindowText(g_hwnd,wndtitle.c_str());
}
void showwindow(int stype){
	ShowWindow(g_hwnd,stype);
}
void showwindow(){
	showwindow(SW_SHOW);
}
void movewindow(int x,int y,int w,int h){
	/*HDC hdcnew;
	if(w>dcw){
		dcw=w;
	}
	if(h>dch){
		dch=h;
	}*/
	MoveWindow(g_hwnd,x,y,w,h,TRUE);
	wndx=x;
	wndy=y;
	wndw=w;
	wndh=h;
}
void poswindow(int x,int y){
	movewindow(x,y,wndw,wndh);
}
void resizewindow(int w,int h){
	movewindow(wndx,wndy,w,h);
}

BOOL CALLBACK gcwProc(HWND hwnd,LPARAM lParam){
	char buf[107]={0};
	GetClassName(hwnd,buf,100);
	if(string(buf)=="ConsoleWindowClass"){
		*((HWND*)lParam)=hwnd;
		return 0;
	}
	return 1;
}
HWND getconsolewindow(){
	return GetConsoleWindow();
}
void hideconsole(){
	HWND hwnd=getconsolewindow(); 
	ShowWindow(hwnd,SW_HIDE);
}

bool windowexist(){
	//printf("now wflg=%d\n",wflg);
	return wflg;
}
void keepwindow(){
	while(windowexist()){
		Sleep(10);
	}
}
void closewindow(){
	SendMessage(g_hwnd,WM_CLOSE,0,0);
}

void setupdateinterval(int ms){
	timerInterv=ms;
}
void autoupdate(int flg){
	autoupd=flg;
}
void stopupdate(){
	autoupdate(0);
}
void continueupdate(){
	autoupdate(1);
}

#endif
