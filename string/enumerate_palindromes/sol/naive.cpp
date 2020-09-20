#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

//template
typedef long long int ll;
const int inf = 0x3fffffff; const ll INF = 0x1fffffffffffffff; const double eps=1e-12;
template<typename T>inline bool chmax(T& a,T b){if(a<b){a=b;return 1;}return 0;}
template<typename T>inline bool chmin(T& a,T b){if(a>b){a=b;return 1;}return 0;}
//end

vector<int> sol(const string& s){
   int n=s.size(); vector<int> res(n*2-1);
   for(int i=0;i<n;i++){
      int k=0;
      while(i-k>=0 and i+k<n and s[i-k]==s[i+k])k++;
      res[i*2]=k*2-1;
   }
   for(int i=0;i<n-1;i++){
      int k=0;
      while(i-k>=0 and i+k+1<n and s[i-k]==s[i+k+1])k++;
      res[i*2+1]=k*2;
   }
   return res;
}

int main(){
   string s; cin>>s;
   auto res=sol(s);
   for(int i=0;i<(int)res.size();i++){
      cout<<res[i]<<(i==(int)res.size()-1?'\n':' ');
   }
   return 0;
}