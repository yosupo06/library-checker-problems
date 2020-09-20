#define _USE_MATH_DEFINES
#include <vector>
#include <string>
#include <iostream>
using namespace std;

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