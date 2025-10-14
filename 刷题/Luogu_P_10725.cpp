#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e6+9;
int a[N],n,px,py,disx,disy;
vector<int>e[N];
inline void dfs(int x,int fa,int diss){
    if(a[x]==0 && diss>disx) disx=diss,px=x;
    if(a[x]==1 && diss>disy) disy=diss,py=x;
    for(auto i:e[x])if(i!=fa)dfs(i,x,diss+1);
}
inline void dfs1(int x,int fa,int diss){
    if(a[x]==1 && diss>disx) disx=diss,px=x;
    for(auto i:e[x])if(i!=fa)dfs1(i,x,diss+1);
}
inline void dfs2(int x,int fa,int diss){
    if(a[x]==0 && diss>disy) disy=diss,py=x;
    for(auto i:e[x])if(i!=fa)dfs2(i,x,diss+1);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        e[x].pb(y);
        e[y].pb(x);
    }
    dfs(1,1,0);
    disx=INT_MIN;
    disy=INT_MIN;
    dfs1(px,px,0);
    dfs2(py,py,0);
    cout<<max(disx,disy);
    return 0;
}