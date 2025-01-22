#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+9;
struct node{
    ll u,v,w;
    bool operator <(const node &y){
        return this->w<y.w;
    }
}e[N];
ll n,m,ans,fa[N],maxx;
inline ll Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline bool Kruskral(int x){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    ll num=0;
    for(int i=x;i<=m;i++){
        if(Find(e[i].u)!=Find(e[i].v)){
            num++;
            maxx=e[i].w;
            fa[Find(e[i].u)]=Find(e[i].v);
        }
        if(num==n-1)break;
    }
    return (num==n-1);
}
int main(){
    while(cin>>n){
        if(n==0) break;
        cin>>m;
        for(int i=1;i<=m;i++)
            cin>>e[i].u>>e[i].v>>e[i].w;
        sort(e+1,e+m+1);
        ans=INT_MAX;maxx=INT_MIN;
        for(int i=1;i<=m;i++){
            maxx=INT_MIN;
            if(Kruskral(i)){
                ans=min(ans,maxx-e[i].w);
            }
        }
        if(ans>10000) cout<<"-1\n";
        else cout<<ans<<endl;
    }
    return 0;
}