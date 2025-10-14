#include<bits/stdc++.h>
#define ll int
#define pb push_back
using namespace std;
const ll N=3e5+9;
ll c[N],n,m,q,root[N],vis[N];
ll d1[N],d2[N],d,fa[N];
vector<ll>e[N];
inline ll Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void merge(int x,int y){
    if(Find(x)==Find(y)) return void();
    fa[Find(x)]=Find(y);
}
inline void dfs(int x,int fa,int rt){
    merge(x,rt);vis[x]=1;
    for(auto i:e[x]){
        if(i==fa) continue;
        dfs(i,x,rt);
        int tmp=d1[i]+1;
        if(tmp>d1[x])
            d2[x]=d1[x],
            d1[x]=tmp;
        else if(tmp>d2[x])
            d2[x]=tmp;
    }
    d=max(d,d1[x]+d2[x]);
}
inline ll C(int x){return (x/2+(x%2));}
int main(){
    cin>>n>>m>>q;
    for(int i=1,x,y;i<=m;i++)
        cin>>x>>y,
        e[x].pb(y),
        e[y].pb(x);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++){
        d=INT_MIN;
        if(!vis[i]){
            dfs(i,i,i);
            c[i]=d;
        }
    }
    int opt,x,y;
    while(q--){
        cin>>opt>>x;
        if(opt==2){
            cin>>y;
            if(Find(x)==Find(y)) continue;
            c[Find(y)]=max(C(c[Find(x)])+C(c[Find(y)])+1,max(c[Find(x)],c[Find(y)]));
            merge(Find(x),Find(y));
        }else cout<<c[Find(x)]<<endl;
    }
    return 0;
}