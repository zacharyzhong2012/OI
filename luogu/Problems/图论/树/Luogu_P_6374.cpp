#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=5e5+9;
int siz[N],dfn[N],dep[N],jp[N][29],n,cnt,q;
vector<int>e[N];
inline void dfs(int x,int fa){
    siz[x]=1;
    dfn[x]=++cnt;
    dep[x]=dep[fa]+1;
    jp[x][0]=fa;
    for(int i=1;i<=19;i++)
        jp[x][i]=jp[jp[x][i-1]][i-1];
    for(auto i:e[x]){
        if(i==fa) continue;
        dfs(i,x);siz[x]+=siz[i];
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--)
        if(dep[jp[x][i]]>=dep[y])
            x=jp[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--)
        if(jp[x][i]!=jp[y][i])
            x=jp[x][i],y=jp[y][i];
    return jp[x][0];
}
inline bool check(int x,int y){return (dfn[y]<=dfn[x] && dfn[y]+siz[y]-1>=dfn[x]);}
inline ll unsiz(int x){return n-siz[x];}
inline ll Jps(int x,int fa){
    if(x==fa) return 0;
    for(int i=19;i>=0;i--)
        if(dep[jp[x][i]]>dep[fa])
            x=jp[x][i];
    return siz[x];
}
int main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        e[x].pb(y);
        e[y].pb(x);
    }
    dfs(1,1);
    while(q--){
        int x,y,z,lca;
        cin>>x>>y>>z;
        lca=LCA(x,y);
        if(z==lca) cout<<n-Jps(x,z)-Jps(y,z)<<endl;
        else if(check(x,z) && !check(y,z)) cout<<n-Jps(x,z)-unsiz(z)<<endl;
        else if(check(y,z) && !check(x,z)) cout<<n-Jps(y,z)-unsiz(z)<<endl;
        else cout<<"0\n";
    }
    return 0;
}