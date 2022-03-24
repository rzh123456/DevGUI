#ifndef _DSTRING_H_
#define _DSTRING_H_

string trim(string s){
	int l=s.size();
	string ret="";
	for(int i=0;i<l;++i){
		if(!isspace(s[i])){
			ret+=s[i];
		}
	}
	return ret;
}
string trimx(string s){
	int l=s.size();
	string ret="";
	for(int i=0;i<l;++i){
		if(!isspace(s[i])){
			if(isalpha(s[i])){
				if(isupper(s[i])){
					ret+=tolower(s[i]);
				}
				else{
					ret+=s[i];
				}
			}
			else{
				ret+=s[i];
			}
		}
	}
	return ret;
}
string vstringf(string fmt,va_list vl){
	char ret[STRLENMX]={""};
	vsprintf(ret,fmt.c_str(),vl);
	return string(ret);
}
string stringf(string fmt,...){
	va_list vl;
	va_start(vl,fmt);
	return vstringf(fmt,vl);
}
string stringfmt(string fmt,...){
	va_list vl;
	va_start(vl,fmt);
	return vstringf(fmt,vl);
}
bool isnumstr(string s){
	int l=s.size();
	for(int i=0;i<l;++i){
		if(!isdigit(s[i])){
			return 0;
		}
	}
	return 1;
}
int strtoint(string s){
	int l=s.size(),t=0;
	for(int i=0;i<l;++i){
		t=10*t+(s[i]&15);
	}
	return t;
}
string lenstr(const char *s,int len){
	string r="";
	for(int i=0;i<len;++i){
		switch(s[i]){
			case '\0':{
				r+="\\0";
				break;
			}
			case ' ':{
				r+="<SPACE>";
				break;
			}
			case '\t':{
				r+="\\t";
				break;
			}
			case '\r':{
				r+="\\r"; 
				break;
			}
			case '\n':{
				r+="\\n"; 
				break;
			}
			case EOF:{
				r+="<EOF>"; 
				break;
			}
			default:{
				r+=s[i];
				break;
			}
		}
	}
	return r;
}

#endif
