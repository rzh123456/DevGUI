#ifndef _DSCRIPT_H_
#define _DSCRIPT_H_

string readfilep(FILE *fl){
	string ret=ESTR;
	char t;
	while((t=fgetc(fl))!=EOF){
		ret+=t;
	}
	return ret;
}
string readfile(string path){
	FILE *hfile=fopen(path.c_str(),"r");
	string ret=readfilep(hfile);
	fclose(hfile);
	return ret;
}
void runcmd(string cmd){
	system(cmd.c_str());
}
string runvbs(string prog){
	string ret;
	FILE *ofl=fopen("dgui_tmp.vbs","w");
	fputs("dim fso,ofl,ret\n",ofl);
	fputs("ret=0\n",ofl);
	fputs("set fso=CreateObject(\"Scripting.FileSystemObject\")\n",ofl);
	fputs("set ofl=fso.CreateTextFile(\"dgui_vbs_ret\", true)\n",ofl);
	fputs((prog+'\n').c_str(),ofl);
	fputs("ofl.Write(ret)\n",ofl);
	fputs("ofl.Close()\n",ofl);
	fputs("set ofl=nothing\n",ofl);
	fputs("set fso=nothing\n",ofl);
	fclose(ofl);
	system("dgui_tmp.vbs");
	FILE *ifl=fopen("dgui_vbs_ret","r");
	ret=readfile("dgui_vbs_ret");
	fclose(ifl);
	DeleteFile("dgui_vbs_ret");
	return ret;
}
string vbsinput(string info,string title=""){
	return runvbs("ret=inputbox(\""+info+"\",\""+title+"\")");
}
int vbsmsgbox(string info,string title,int mstyle){
	return strtoint(runvbs(stringf("ret=msgbox(\"%s\",%d,\"%s\")",info.c_str(),mstyle,title.c_str())));
}

#endif
