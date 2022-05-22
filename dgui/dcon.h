#ifndef _DCON_H_
#define _DCON_H_

#ifdef DGUI_PROJECT

HANDLE hCon;
void openconsole(void){
	if(hCon==NULL){ 
		AllocConsole();  
		hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	}
}
void OpenConsole(void){
	openconsole();
}
void consoleout(string str){
	long unsigned ccnt;
	WriteConsole(hCon,str.c_str(),str.size(),&ccnt,NULL);
	UNUSED(ccnt);
}
void ConsoleOut(string str){
	consoleout(str);
}
void cputs(const char *s){
	consoleout(string(s)+'\n');
}
char cputc(char c){
	string s="";
	s+=c;
	consoleout(s);
	return c;
}
int vcprintf(const char *fmt,va_list vl){
	char out[STRLENMX]={""};
	int ret;
	ret=vsprintf(out,fmt,vl);
	consoleout(out);
	return ret;
}
int cprintf(const char *fmt,...){
	va_list vl;
	va_start(vl,fmt);
	return vcprintf(fmt,vl);
}

#define printf cprintf
#define puts cputs
#define putchar cputc

#endif

#endif
