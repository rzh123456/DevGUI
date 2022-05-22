#ifndef _DEFFECT_H_
#define _DEFFECT_H_

typedef class AREADATAMEM{
    public:
        int w,h;
        DCOLOR *dat;
}*PAREADATAMEM,*AREADATA;

//typedef DCOLOR(*COLORFILTER)(DCOLOR);
//typedef COLORFILTER COLFLTR;

DCOLOR &getpxfromarea(AREADATA dta,int x,int y){
	return dta->dat[(dta->w)*y+x];
}
void copyarea(AREADATA src,AREADATA buf){
	int w=src->w,
		h=src->h;
	for(int i=0;i<w;++i){
		for(int j=0;j<h;++j){
			getpxfromarea(buf,i,j)=getpxfromarea(src,i,j);
		}
	}
}

template <typename FilterT> 
void dofilter(FilterT fltr,int x,int y,int w,int h){
	DCOLOR *dt=new DCOLOR[w*h+3];
	AREADATA ad=new AREADATAMEM;
	ad->w=w;
	ad->h=h;
	ad->dat=dt;
	for(int i=0;i<w;++i){
		for(int j=0;j<h;++j){
			getpxfromarea(ad,i,j)=getpxcol(x+i,y+j); 
		}
	}
	fltr(ad);
	for(int i=0;i<w;++i){
		for(int j=0;j<h;++j){
			setpxcol(x+i,y+j,getpxfromarea(ad,i,j));
		}
	}
	delete[] dt;
	delete ad;
	Sleep(20);
}

class MosaicFilter{
	private:
		int deg;
	public:
		MosaicFilter(const int &_d):
			deg(_d){} 
		void operator()(AREADATA ad){
			int w=ad->w,
				h=ad->h;
			for(int i=0;i<w;++i){
				for(int j=0;j<h;++j){
					getpxfromarea(ad,i,j)=getpxfromarea(ad,i-i%deg,j-j%deg); 
				}
			}
		}
};
class BlurFilter{
	private:
		int deg;
	public:
		BlurFilter(const int &_d):
			deg(_d){}
		void operator()(AREADATA ad){
			int w=ad->w,
				h=ad->h;
			DCOLOR *dt=new DCOLOR[w*h+3];
			AREADATA tmp=new AREADATAMEM;
			DCOLOR t1,t2,t3,t4;
			tmp->w=w,
			tmp->h=h,
			tmp->dat=dt;
			copyarea(ad,tmp);
			for(int i=deg;i<w-deg;++i){
				for(int j=deg;j<h-deg;++j){
					t1=getpxfromarea(ad,i,j-deg);
					t2=getpxfromarea(ad,i,j+deg);
					t3=getpxfromarea(ad,i-deg,j);
					t4=getpxfromarea(ad,i+deg,j);
					getpxfromarea(tmp,i,j)=getRGB(
						dround(1.0*(getR(t1)+getR(t2)+getR(t3)+getR(t4))/4),
						dround(1.0*(getG(t1)+getG(t2)+getG(t3)+getG(t4))/4),
						dround(1.0*(getB(t1)+getB(t2)+getB(t3)+getB(t4))/4)
					);
				}
			}
			copyarea(tmp,ad);
			delete dt;
			delete tmp;
		}
};

template <typename ColorFilterT>
class ColFilter{
	private:
		typedef ColorFilterT CF;
		CF cfltr;
	public:
		//ColFilter(){}
		ColFilter(const CF &_cf):
			cfltr(_cf){}
		void operator()(AREADATA ad){
			int w=ad->w,
				h=ad->h;
			for(int i=0;i<w;++i){
				for(int j=0;j<h;++j){
					getpxfromarea(ad,i,j)=cfltr(getpxfromarea(ad,i,j)); 
				}
			}
		}
};

template <typename ColorFilterT>
void docolorfilter(ColorFilterT fltr,int x,int y,int w,int h){
	dofilter(ColFilter<ColorFilterT>(fltr),x,y,w,h);
}

class BrightenFilter{
	private:
		int deg;
	public:
		BrightenFilter(const int &_d):
			deg(_d){} 
		DCOLOR operator()(DCOLOR col){
			return getRGB(
				imin(255,getR(col)+deg),
				imin(255,getG(col)+deg),
				imin(255,getB(col)+deg)
			);
		}
};
class GreyFilter{
	private:
		int deg;
	public:
		GreyFilter(const int &_d):
			deg(_d){}
		DCOLOR operator()(DCOLOR col){
			int tmp=(getR(col)+getG(col)+getB(col))/3; 
			return getRGB(tmp,tmp,tmp);
		}
		/* TODO (#1#): GreyFilter Deg */
};

void brighten(int x,int y,int w,int h,int deg){
	docolorfilter(BrightenFilter(deg),x,y,w,h);
}
void darken(int x,int y,int w,int h,int deg){
	docolorfilter(BrightenFilter(-deg),x,y,w,h);
}
void grey(int x,int y,int w,int h,int deg){
	docolorfilter(GreyFilter(deg),x,y,w,h);
}
void grey(int x,int y,int w,int h){
	grey(x,y,w,h,1000);
}
void mosaic(int x,int y,int w,int h,int deg){
	dofilter(MosaicFilter(deg),x,y,w,h);
}
void blur0(int x,int y,int w,int h){
	dofilter(BlurFilter(1),x,y,w,h);
}
void blur(int x,int y,int w,int h,int deg){
	while(deg--){
		blur0(x,y,w,h);
	}
}
 

#endif 
