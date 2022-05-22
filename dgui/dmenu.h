#ifndef _DMENU_H_
#define _DMENU_H_

typedef class DMENUNODE *DMENUTREE;
typedef DMENUTREE DMENU,MENU;
typedef vector<MENU> DMENUCHILDREN;
struct DMENUNODE{
    private:
        DMENUCHILDREN ch;
        string txt;
        uint cmd;
        int sep,chk,ena;
    public:
        MENU child(int idx){
            return ch[idx];
        }
        DMENUCHILDREN children(){
            return ch;
        }
        int chcnt(){
            return ch.size();
        }
        bool leaf(){
            return ch.empty();
        }
        void settext(string _t){
        	txt=_t;
		}
		void setcmd(uint c){
			cmd=c;
		}
		string gettext(){
			return txt;
		}
		uint getcmd(){
			return cmd;
		}
		void appendchild(MENU mb){
			ch.push_back(mb);
		}
		void separator(int v){
			sep=v;
		}
		void check(int v){
			chk=v;
		}
		void enable(int v){
			ena=v;
		}
		int isseparator(){
			return sep;
		}
		int ischecked(){
			return chk;
		}
		int enabledstatus(){
			return ena;
		}
        ~DMENUNODE(){}
};
MENU newmenu(){
    return new DMENUNODE;
}
MENU newmenu(string t,uint cmd,int sep,int chk,int ena){
    MENU ret=new DMENUNODE;
    ret->settext(t);
    ret->setcmd(cmd);
    ret->separator(sep);
    ret->check(chk);
    ret->enable(ena);
    return ret;
}
MENU newmenu(string t,uint cmd){
    return newmenu(t,cmd,0,0,0);
}
MENU newmenu(string t){
    return newmenu(t,0);
}
MENU newseparator(){
    return newmenu("",0,1,0,0);
}
void appendchildmenu(MENU buf,MENU x){
	buf->appendchild(x);
}
void delmenu(MENU mn){
    if(mn==NULL){
        return;
    }
    for(int i=0;i<(mn->chcnt());++i){
        delmenu(mn->child(i));
    }
    delete mn;
}
void setallsubmenu(HMENU hmn,MENU mn){
	for(int i=0;i<(mn->chcnt());++i){
		int flg=0;
		if(mn->child(i)->ischecked()){
			flg|=MF_CHECKED;
		}
		if(mn->child(i)->enabledstatus()==0);
		else if(mn->child(i)->enabledstatus()==1){
			flg|=MF_GRAYED;
		}
		else{
			flg|=MF_DISABLED;
		}
		if(mn->child(i)->isseparator()){
			AppendMenu(hmn,MF_SEPARATOR,0,"");
		}
		else if(mn->child(i)->leaf()){
			AppendMenu(hmn,MF_STRING|flg,mn->child(i)->getcmd(),mn->child(i)->gettext().c_str());
		}
		else{
			HMENU hpop=CreateMenu();
			setallsubmenu(hpop,mn->child(i));
			AppendMenu(hmn,MF_POPUP|flg,(UINT_PTR)hpop,mn->child(i)->gettext().c_str());
		}
    }
}
void setmenu(MENU mn){
    HMENU hmn=CreateMenu();
    setallsubmenu(hmn,mn);
    SetMenu(g_hwnd,hmn);
    DrawMenuBar(g_hwnd);
    /* TODO (Admin#2#): Release Old? */
}

#endif
