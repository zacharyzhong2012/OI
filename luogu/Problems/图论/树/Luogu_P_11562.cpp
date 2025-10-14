#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e6+9;
vector<int>e[N];
int n,x,dis,pos,a[N],num;
inline void dfs1(int x,int diss,int fa){
  //  cout<<x<<' '<<diss<<' '<<fa<<endl;
    if(a[fa]!=a[x]) diss++;
    if(diss>dis && a[x]==1) dis=diss,pos=x;
    for(auto i:e[x])if(i!=fa)dfs1(i,diss,x);
}
inline void dfs2(int x,int diss,int fa){
    if(a[fa]!=a[x]) diss++;
    if(diss>dis && a[x]==1) dis=diss,pos=x;
    for(auto i:e[x])if(i!=fa)dfs2(i,diss,x);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i],num|=a[i];
    if(!num) return cout<<0,0;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,e[x].pb(y),e[y].pb(x);
    dfs1(1,0,0);
    dfs2(pos,0,pos);
    cout<<dis/2+1;
    return 0;
}