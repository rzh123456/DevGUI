#ifndef _DDS_H_
#define _DDS_H_

template <typename T>
class DGHash{
	public:
		static unsigned MOD;
		DGHash(){} 
		inline unsigned operator()(T);
};

template <>
class DGHash<string>{
	public:
		static const long long unsigned MOD=10007;
		static const long long unsigned BAS=257;
		DGHash(){} 
		inline long long unsigned operator()(string s){
			long long unsigned r=0;
			for(long long unsigned i=0;i<s.size();++i){
				r=(r*BAS%MOD+s[i])%MOD;
			}
			return (long long unsigned )(r);
		}
};

template <typename KeyT,typename ValT,typename HshT=DGHash<string> >
class DGHashmap{
	private:
		typedef vector<pair<KeyT,ValT> > ConT;
		vector<ConT> dat;
		HshT hs;
		template <typename T>
		inline void cs(T &v,long long unsigned s){
			if(v.size()<s+1){
				v.reserve(s+1);
				v.resize(s+1);
			}
		}
	public:
		DGHashmap(){}
		void insert(KeyT k,ValT v){
			long long unsigned p=hs(k);
			cs(dat,p);
			for(long long unsigned i=0;i<dat[p].size();++i){
				if(dat[p][i].first==k){
					dat[p][i].second=v;
					return;
				}
			}
			dat[p].push_back(make_pair(k,v));
		}
		ValT &query(KeyT k){
			long long unsigned p=hs(k);
			cs(dat,p);
			for(long long unsigned i=0;i<dat[p].size();++i){
				if(dat[p][i].first==k){
					return dat[p][i].second;
				}
			}
			dat[p].push_back(make_pair(k,ValT()));
			return dat[p][dat[p].size()-1].second;
		}
		ValT &operator[](KeyT k){
			return query(k);
		}
};

#endif
