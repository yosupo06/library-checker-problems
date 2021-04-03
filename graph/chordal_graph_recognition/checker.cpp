#include <vector>
#include <set>
#include "testlib.h"

using namespace std;

int n,m;
std::vector<std::set<int> > adj;

inline string readAndCheckAnswer(InStream& stream) {
  string yesno=upperCase(stream.readWord());
  if(yesno=="YES"){
    //read ordering of vertices
    std::vector<int> order;
    std::vector<int> ind(n);
    std::vector<bool> used(n,false);
    for(int i=0;i<n;i++){
      int v=stream.readInt(0,n-1,format("order[%d]",i).c_str());
      if(used[v]){
	stream.quitf(_wa,"vertex %d was used twice",v);
      }
      used[v]=true;
      order.push_back(v);
      ind[v]=i;
    }
    //check if it is a perfect elimination ordering
    for(int i=n-1;i>=0;i--){
      int x=order[i];
      int succ=n+1;//index of neighbor first in order after x
      for(int y:adj[x]){
	if(ind[y]>ind[x]&&ind[y]<succ){
	  succ=ind[y];
	}
      }
      if(succ==n+1) continue;
      int z=order[succ];//neighbor first in order after x
      //check that neighbors of x that appear after x form a clique
      //it suffices to check that all neighbors of x that appear after z are neighbors of z, since neighbors of z that appear after z form a clique
      for(int y:adj[x]){
	if(ind[y]>ind[z]&&!adj[z].count(y)){
	  stream.quitf(_wa,"Neighbors %d and %d appear after %d in the ordering but are not adjacent",y,z,x);
	}
      }
    }
  }else if(yesno=="NO"){
    //read cycle of vertices
    int k=stream.readInt(4,n,"cycle length");
    std::vector<int> cycle;
    std::vector<bool> used(n,false);
    for(int i=0;i<k;i++){
      int v=stream.readInt(0,n-1,format("cycle[%d]",i).c_str());
      if(used[v]){
	stream.quitf(_wa,"vertex %d was used twice",v);
      }
      used[v]=true;
      cycle.push_back(v);
    }
    //check if it is a cycle
    for(int i=0;i<k;i++){
      int x=cycle[i],y=cycle[(i+1)%k];
      if(!adj[x].count(y)){
	stream.quitf(_wa,"Bad cycle: no edge between %d and %d",x,y);
      }
    }
    //check if it is an induced cycle
    for(int i=0;i<k;i++){
      int x=cycle[i],a=cycle[(i+1)%k],b=cycle[(i+k-1)%k];
      for(int y:adj[x]){
	if(used[y]&&y!=a&&y!=b){
	  stream.quitf(_wa,"Cycle not induced: edge between %d and %d",x,y);
	}
      }
    }
  }else{
    stream.quitf(_wa,"Answer did not begin with YES or NO");
  }
  return yesno;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    n = inf.readInt();
    m = inf.readInt();
    adj.resize(n);
    for(int i=0;i<m;i++){
      int a=inf.readInt();
      int b=inf.readInt();
      adj[a].insert(b);
      adj[b].insert(a);
    }

    string ans_yesno=readAndCheckAnswer(ans);
    string ouf_yesno=readAndCheckAnswer(ouf);
    if(ans_yesno!=ouf_yesno){
      quitf(_fail,"checker incorrect");
    }
    quitf(_ok, "n=%d, m=%d ans=%s", n, m, ans_yesno.c_str());
}
