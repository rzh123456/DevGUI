#ifndef _DGUI_DOBJ_H_
#define _DGUI_DOBJ_H_

/*enum DGO_Tag{
	OT_ELLIPSE,
	OT_CIRCLE,
	OT_RECT,
	OT_PARA,
	OT_SQUARE,
	OT_TEXT
};*/
class DGO_Setup{
	private:
	public:
		DGO_Setup();
};
class DGO_Ellipse{
	private:
		DGO_Ellipse();
	public:
		int r1,r2;
		DGO_Ellipse(const int &_r1,const int &_r2):
			r1(_r1),r2(_r2){} 
};
class DGO_Move{
	private:
		DGO_Move();
	public:
		int x,y;
		DGO_Move(const int &_x,const int &_y):
			x(_x),y(_y){} 
};
class DGO_Line{
	private:
		DGO_Line();
	public:
		int x,y;
		DGO_Line(const int &_x,const int &_y):
			x(_x),y(_y){} 
};
class DGO_Rect{
	private:
		DGO_Rect();
	public:
		int a,b;
		DGO_Rect(const int &_a,const int &_b):
			a(_a),b(_b){} 
};
class DGO_Text{
	private:
		DGO_Text();
	public:
		string s;
		DGO_Text(const string &_s):
			s(_s){}
};
class DevGUIObj{
	private:
		DPOINT pos;
	public:
		DevGUIObj(){
			pos=DPOINT(0,0);
		}
		inline DPOINT getpos(){
			return pos;
		}
		void moveto(int x,int y){
			pos=DPOINT(x,y);
		}
		void line(int x2,int y2){
			dgui_ns::line(pos.x,pos.y,x2,y2);
		}
		void lineto(int x2,int y2){
			line(x2,y2);
			moveto(x2,y2);
		}
		void ellipse(int r1,int r2){ 
			dgui_ns::ellipse(pos.x,pos.y,r1,r2);
		}
		void circle(int r){
			dgui_ns::circle(pos.x,pos.y,r);
		}
		void rect(int a,int b){
			dgui_ns::rectangle(pos.x,pos.y,a,b);
		}
		void square(int a){
			dgui_ns::square(pos.x,pos.y,a); 
		}
		void textout(string s){
			dgui_ns::textout(pos.x,pos.y,s);
		}
		void text(string s){
			dgui_ns::textout(pos.x,pos.y,s);
		}
		void vtextoutf(string fmt,va_list vl){
			dgui_ns::vtextoutf(pos.x,pos.y,fmt,vl);
		}
		void textoutf(string fmt,...){
			va_list vl;
			va_start(vl,fmt);
			dgui_ns::vtextoutf(pos.x,pos.y,fmt,vl);
		}
		void clear(){
			dgui_ns::clear();
		}
		DevGUIObj &operator<<(const DGO_Move &b){
			moveto(b.x,b.y);
			return (*this);
		}
		DevGUIObj &operator<<(const DGO_Ellipse &b){
			ellipse(b.r1,b.r2);
			return (*this);
		}
		DevGUIObj &operator<<(const DGO_Rect &b){
			rect(b.a,b.b);
			return (*this);
		}
		DevGUIObj &operator<<(const DGO_Text &b){
			textout(b.s);
			return (*this);
		}
		DevGUIObj &operator<<(const string &s){
			textout(s);
			return (*this);
		}
}DevGUI;

DGO_Move moveto(int x,int y){
	return DGO_Move(x,y);
}
DGO_Ellipse ellipse(int r1,int r2){
	return DGO_Ellipse(r1,r2);
}
DGO_Ellipse circle(int r){
	return DGO_Ellipse(r,r);
}
DGO_Rect rect(int a,int b){
	return DGO_Rect(a,b);
}
DGO_Rect square(int a){
	return DGO_Rect(a,a);
}
DGO_Text textout(string s){
	return DGO_Text(s);
}
DGO_Text text(string s){
	return DGO_Text(s);
}
DGO_Text textoutf(string fmt,...){
	va_list vl;
	va_start(vl,fmt);
	return DGO_Text(vstringf(fmt,vl));
}

#define devgui DevGUI
#define GUI_stream DevGUI
#define turtle DevGUI

#ifndef DGUI_OLDVER
#define dgui DevGUI
#endif

#endif
