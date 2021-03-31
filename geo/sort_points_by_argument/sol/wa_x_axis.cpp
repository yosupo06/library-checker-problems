#include <cstdio>
using std::fread; using std::fwrite;
#include <algorithm>
using std::sort;
char buf[4800007], *i=buf,*l,*r;
struct pt {
  long long x,y;
} pts[200000];
bool cmp(const pt&a,const pt&b){
  if (!a.x&&!a.y)return b.y>=0;
  if (!b.x&&!b.y)return a.y<0;
  if (a.x*b.y>b.x*a.y) return !(b.y<0&&a.y>=0);
  else return a.y<0&&b.y>=0;
}
unsigned N;
int x,y;bool neg;
int main() {
  buf[fread(buf,1,sizeof buf,stdin)]='\n';
  while(*i!='\n')N=N*10+*i++-'0';
  ++i;
  for (unsigned j=0;j<N;++j){
    x=y=neg=0;
    if(*i=='-')neg=1,++i;
    while(*i!=' ')x=x*10+*i++-'0';
    if(neg)x=-x;
    ++i;
    neg=0;
    if(*i=='-')neg=1,++i;
    while(*i!='\n')y=y*10+*i++-'0';
    if(neg)y=-y;
    ++i;
    char temp=*i;*i=0;
    *i=temp;
    pts[j].x=x;pts[j].y=y;
  }
  sort(pts,pts+N,cmp);
  i=buf;
  for(unsigned j=0;j<N;++j){
    x=pts[j].x;y=pts[j].y;
    if(x<0)*i++='-',x=-x;
    l=i;while(x)*i++=x%10+'0',x/=10;
    if(i==l)*i++='0';
    for(r=i-1;l<r;++l,--r)*l^=*r,*r^=*l,*l^=*r;
    *i++=' ';
    if(y<0)*i++='-',y=-y;
    l=i;while(y)*i++=y%10+'0',y/=10;
    if(i==l)*i++='0';
    for(r=i-1;l<r;++l,--r)*l^=*r,*r^=*l,*l^=*r;
    *i++='\n';
  }
  fwrite(buf,1,i-buf,stdout);
}