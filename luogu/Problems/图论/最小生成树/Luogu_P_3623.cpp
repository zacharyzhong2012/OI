#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+9;
struct edge1{ll u,v;}e1[N];
struct edge2{ll u,v;}e2[N];
ll n,m,k,cnt1,cnt2,fa[N],f1[N],f2[N];
inline ll Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(w==0) e1[++cnt1]={u,v};
        else e2[++cnt2]={u,v};
    }
    for(int i=1;i<=n;i++)fa[i]=i;
    ll num=0;
    for(int i=1;i<=cnt1;i++){
        if(Find(e1[i].u)!=Find(e1[i].v)){
            num++;
            fa[Find(e1[i].u)]=Find(e1[i].v);
            f1[i]=1;
        }
        if(num==k)break;
    }
    if(num!=k) return cout<<"no solution",0;
    for(int i=1;i<=cnt2;i++){
        if(Find(e2[i].u)!=Find(e2[i].v)){
            num++;
            fa[Find(e2[i].u)]=Find(e2[i].v);
            f2[i]=1;
        }
        if(num==n-1)break;
    }
    if(num!=n-1) return cout<<"no solution",0;
    for(int i=1;i<=cnt1;i++)
        if(f1[i]){
            cout<<e1[i].u<<' '<<e1[i].v<<" 0\n";
        }
    for(int i=1;i<=cnt2;i++)
        if(f2[i]){
            cout<<e2[i].u<<' '<<e2[i].v<<" 1\n";
        }
    return 0;
}