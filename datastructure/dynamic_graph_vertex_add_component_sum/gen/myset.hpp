#include<math.h>
using namespace::std;
template<typename T>
class myset{
    struct node{
        T val;
        int cnt=1,cnt2=1,dep=0,f=1;
        static const node* nil;
        node* ch[2]={nullptr,nullptr};
        node(T val):val(val){}
    };
    using np=node*;
    np root=nullptr;
    inline int count(np t){return t?t->cnt:0;}
    inline int count2(np t){return t?t->cnt2:0;}
    inline int depth(np t){return t?t->dep:0;}
    np update(np t,bool f=1){
		if(!t)return t;
        t->cnt=count(t->ch[0])+1+count(t->ch[1]);
        t->cnt2=count2(t->ch[0])+(t->f)+count2(t->ch[1]);
        t->dep=max(depth(t->ch[0]),depth(t->ch[1]))+1;
        if(f&&abs(depth(t->ch[0])-depth(t->ch[1]))==2){
            bool b=depth(t->ch[0])<depth(t->ch[1]);
			if(t->ch[b]&&depth(t->ch[b]->ch[b])<depth(t->ch[b]->ch[1-b])){
                t->ch[b]=rot(t->ch[b]);
            }
            t=rot(update(t,0));
		}
        return t;
    }
    np rot(np t){
        int b=depth(t->ch[0])<depth(t->ch[1]);
		np s=t->ch[b];
		t->ch[b]=s->ch[1-b];
		s->ch[1-b]=t;
        update(t,0);
        return update(s,0);
    }
    np insert(T val,np t){
        if(!t)return new node(val);
        bool b=t->val<val;
        t->ch[b]=insert(val,t->ch[b]);
        return update(t);
    }
    np erase(T val,np t){
        if(!t)return t;
        if(t->val==val&&t->f)t->f=0;
        else{
            bool b=t->val<val;
            t->ch[b]=erase(val,t->ch[b]);
        }
        return update(t);
    }
    int lower_bound(T val,np t){
        if(!t)return 0;
        bool b=val>t->val;
        return(b?count2(t->ch[0])+(t->f):0)+lower_bound(val,t->ch[b]);
    }
	int upper_bound(T val,np t){
        if(!t)return 0;
        bool b=val>=t->val;
        return(b?count2(t->ch[0])+(t->f):0)+upper_bound(val,t->ch[b]);
    }
    T find_by_order(int idx,np t){
		if(idx==count2(t->ch[0])&&t->f)return t->val;
        bool b=idx>=count2(t->ch[0]);
		return find_by_order(idx-(b?count2(t->ch[0])+(t->f):0),t->ch[b]);
	}
    public:
    void insert(T val){root=insert(val,root);}
    void erase(T val){root=erase(val,root);}
    inline int size(){return count2(root);}
    inline int count(T val){return upper_bound(val,root)-lower_bound(val,root);}
    inline int count(T l,T r){return lower_bound(r,root)-lower_bound(l,root);}
    //0-indexでidx番目
    inline T operator[](int idx){return find_by_order(idx,root);}
    //x未満の個数/s[lower_bound(x)]はx以上最小の値
    inline int lower_bound(T x){return lower_bound(x,root);}
    //x以下の個数/s[upper_bound(x)]はxより大きい最小の値
	inline int upper_bound(T x){return upper_bound(x,root);}
};