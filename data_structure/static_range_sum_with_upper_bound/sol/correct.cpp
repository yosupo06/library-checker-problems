#include<iostream>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;

template<typename T>
struct MergeSortTree{
    int n;
	vector<vector<T> >dat;
	vector<vector<long> >sum;

    // 和がいらない場合 sum_mode : false にするほうがよい
	MergeSortTree(const vector<T>&v={},bool sum_mode = true)
	{
		n=1;
		while(n<(int)v.size())n<<=1;
		dat.assign(2*n-1,{});
		if(sum_mode) sum.assign(2*n-1,{});
		for(int i=0;i<(int)v.size();i++)
		{
			dat[i+n-1].push_back(v[i]);
      if(sum_mode){
        sum[i+n-1].push_back(0);
			  sum[i+n-1].push_back(v[i]);
      }
		}
		for(int i=n-2;i>=0;i--)
		{
			dat[i].resize(dat[i*2+1].size()+dat[i*2+2].size());
			merge(dat[i*2+1].begin(),dat[i*2+1].end(),
				dat[i*2+2].begin(),dat[i*2+2].end(),
				dat[i].begin()
			);
      if(sum_mode){
        sum[i].resize(dat[i].size()+1,0LL);
			  for(int j=0;j<(int)dat[i].size();j++)sum[i][j+1]=sum[i][j]+dat[i][j];
      }
		}
	}

    //[a,b) sum(*<x)
	long long less_sum(int a,int b,T x,int k=0,int l=0,int r=-1)const{
		if(r<0)r=n;
		if(b<=l||r<=a)return 0LL;
		else if(a<=l&&r<=b)
		{
			int L=lower_bound(dat[k].begin(),dat[k].end(),x)-dat[k].begin();
			return sum[k][L];
		}
		else return less_sum(a,b,x,k*2+1,l,(l+r)/2)+less_sum(a,b,x,k*2+2,(l+r)/2,r);
	}

    //[a,b) sum(*<=x)
    long long lower_sum(int a,int b,T x,int k=0,int l=0,int r=-1)const{
        return less_sum(a,b,x+1,k,l,r);
    }

    //[a,b) count(*<x)
    int less_cnt(int a,int b,T x,int k=0,int l=0,int r=-1)const{
        if(r<0)r=n;
        if(b<=l||r<=a)return 0;
        else if(a<=l&&r<=b)return lower_bound(dat[k].begin(),dat[k].end(),x)-dat[k].begin();
        else return less_cnt(a,b,x,k*2+1,l,(l+r)/2)+less_cnt(a,b,x,k*2+2,(l+r)/2,r);
    }

    //[a,b) count(*<=x)
    int lower_cnt(int a,int b,T x,int k=0,int l=0,int r=-1)const{
        return less_cnt(a,b,x+1,k,l,r);
    }

};

int main(){
    int n,q;
    scanf("%d %d",&n,&q);

    vector<long long> a(n);
    for(int i = 0;i < n;i++) scanf("%lld",&a[i]);

    MergeSortTree<long long> mst(a);

    for(int query = 0;query < q;query++){
        int t,l,r,x;
        scanf("%d %d %d %d",&t,&l,&r,&x);
        if(t == 0){
            int ans = mst.lower_cnt(l,r,x);
            printf("%d\n",ans);
        }else{
            long long ans = mst.lower_sum(l,r,x);
            printf("%lld\n",ans);
        }
    }

    return 0;
}