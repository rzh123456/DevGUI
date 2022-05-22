#ifndef _DWEB_H_
#define _DWEB_H_

int downloadfile(string url,string path){
	return URLDownloadToFile(NULL,url.c_str(),path.c_str(),0,NULL);
}

#endif
