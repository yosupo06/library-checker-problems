#include <cstdio>
#include <vector>
#include <map>
#include <stdint.h>
#include <algorithm>

struct Point{
  int64_t x,y;
  Point operator-(Point p)const{
    return {x-p.x,y-p.y};
  }
  int64_t cross(Point p)const{
    return x*p.y-y*p.x;
  }
  int64_t dot(Point p)const{
    return x*p.x+y*p.y;
  }
  bool operator<(Point p)const{
    if(y!=p.y) return y<p.y;
    return x<p.x;
  }
  bool operator==(Point p)const{
    return x==p.x&&y==p.y;
  }
  Point operator-()const{
    return {-x,-y};
  }
};

int64_t cross(Point a,Point b,Point c){
  return (b-a).cross(c-a);
}

std::map<Point,int> id;
std::vector<Point> ps;
int layer[200005];
int ans[200005];

int main(){
  int N;
  scanf("%d",&N);
  for(int i=0;i<N;i++){
    int X,Y;
    scanf("%d %d",&X,&Y);
    ps.push_back({X,Y});
    id[{X,Y}]=i;
  }
  std::sort(ps.begin(),ps.end());
  for(int l=1,cnt=0;cnt<N;l++){
    std::vector<int> hull;
    for(int i=0;i<N;i++){
      if(layer[i]&&layer[i]!=l) continue;
      while(hull.size()>=2&&cross(ps[hull[hull.size()-2]],ps[hull.back()],ps[i])>0){
	hull.pop_back();
      }
      hull.push_back(i);
    }
    for(int i:hull){
      if(!layer[i]) cnt++;
      layer[i]=l;
    }
    hull.clear();
    for(int i=N-1;i>=0;i--){
      if(layer[i]&&layer[i]!=l) continue;
      while(hull.size()>=2&&cross(ps[hull[hull.size()-2]],ps[hull.back()],ps[i])>0){
	hull.pop_back();
      }
      hull.push_back(i);
    }
    for(int i:hull){
      if(!layer[i]) cnt++;
      layer[i]=l;
    }
  }
  for(int i=0;i<N;i++){
    ans[id[ps[i]]]=layer[i];
  }
  for(int i=0;i<N;i++){
    printf("%d\n",ans[i]);
  }
}
