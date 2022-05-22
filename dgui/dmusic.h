#ifndef _DMUSIC_H_
#define _DMUSIC_H_

#ifndef _NO_MUSICAL_NOTES_

#define qdo 262
#define qre 294
#define qmi 330
#define qfa 349
#define qso 392
#define qla 440
#define qsi 494
#define _do 523
#define re 578
#define mi 659
#define fa 698
#define so 784
#define la 880
#define si 988
#define do1 1046
#define re1 1175
#define mi1 1318
#define fa1 1480
#define so1 1568
#define la1 1760
#define si1 1976
#define sqdo 277
#define sqre 311
#define sqfa 370
#define sqso 415
#define sqla 466
#define sdo 554
#define sre 622
#define sfa 740
#define sso 831
#define sla 932
#define sdo1 1046
#define sre1 1245
#define sfa1 1480
#define sso1 1661
#define sla1 1865

#define qpai 2000
#define dpai 1000
#define pai 500
#define ban 250
#define banban 125

#endif

void beep(int freq,int tim){
	Beep(freq,tim);
	//Sleep(tim);
}

void playmusic(string path){
	PlaySound(path.c_str(),NULL,SND_FILENAME|SND_ASYNC);
}
void finishmusic(string path){
	PlaySound(path.c_str(),NULL,SND_FILENAME|SND_SYNC);
}
void playmusicuntilend(string path){
	finishmusic(path);
}
void playmusicloop(string path){
	PlaySound(path.c_str(),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
}
void stopmusic(string path){
	PlaySound(path.c_str(),NULL,SND_FILENAME|SND_PURGE);
}
void stopallmusic(){
	PlaySound(NULL,NULL,SND_FILENAME);
}

#endif
