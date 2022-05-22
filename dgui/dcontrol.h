#ifndef _DCONTROL_H_
#define _DCONTROL_H_

struct DControl{
	HWND hw;
	DControl(){}
	DControl(const HWND _h):
		hw(_h){} 
};

DControl button(int x,int y,int w,int h,string s,int cmd){
	HWND hw=CreateWindowEx(0,"Button",s.c_str(),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,x,y,w,h,g_hwnd,(HMENU)((long long)(cmd)),g_hInst,NULL);
	SendMessage(g_hwnd,WM_PAINT,0,0);
	return DControl(hw);
}

void deletecontrol(const DControl &c){
	CloseWindow(c.hw);
}

#endif
