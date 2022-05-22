#ifndef _DEVENT_H_
#define _DEVENT_H_

#define transepara transany

typedef string EVENT;
typedef ANYTYPE EPARA;
typedef void(*EFUNC)(EPARA);
typedef void(*EFUNC_NOPARA)();
typedef queue<EFUNC> EQUEUE;
struct EVENTINFO{
	EVENT ev;
	EPARA pa;
	EVENTINFO(){}
	EVENTINFO(const EVENT &_e,const EPARA _p):
		ev(_e),pa(_p){} 
};
 
DGHashmap<EVENT,EQUEUE> events;

void syncevent(EVENT ev,EPARA para){
	EQUEUE eq=events[ev];
	while(!eq.empty()){
		EFUNC ef=eq.front();
		ef(para);
		eq.pop();
	}
}//同步(单线) 
unsigned __stdcall evthread(void *info){
	EVENTINFO *ei=(EVENTINFO*)info;
	syncevent(ei->ev,ei->pa);
	delete ei;
	return 0;
}
void asyncevent(EVENT ev,EPARA para){
	unsigned tID;
	EVENTINFO *ei=new EVENTINFO(ev,para);
	_beginthreadex(NULL,0,evthread,ei,0,&tID);
}//异步(多线) 

void dbind(EVENT ev,EFUNC fun){
	events[ev].push(fun);
}
void bind(EVENT ev,EFUNC fun){
	dbind(ev,fun);
}

#endif
