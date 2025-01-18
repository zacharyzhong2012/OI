#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define P pair<ll,ll>
using namespace std;
const ll N=1e5+9;
ll fa[N][40],jp[N][40][2],dis[N];
ll n,q,dep[N];
vector<P>e[N];
inline void dfs(int x,int fat)
{
//	cout<<x<<' '<<fat<<endl;
    fa[x][0]=fat;dep[x]=dep[fat]+1;
    for(int i=1;i<=20;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1],
        jp[x][i][0]=min(jp[x][i-1][0],jp[fa[x][i-1]][i-1][0]),
        jp[x][i][1]=max(jp[x][i-1][1],jp[fa[x][i-1]][i-1][1]);
    for(auto i:e[x])
        if(i.fi!=fat){
        //	cout<<i.fi<<' '<<i.se<<endl;
            jp[i.fi][0][0]=jp[i.fi][0][1]=i.se;
            dfs(i.fi,x);
        }
} 
inline P LCA(int x,int y){
    ll minn=INT_MAX,maxx=INT_MIN;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y]){
            minn=min(minn,jp[x][i][0]);
            maxx=max(maxx,jp[x][i][1]);
            x=fa[x][i];
        }
    if(x==y) return {minn,maxx};
    for(int i=20;i>=0;i--)
        if(fa[x][i]!=fa[y][i]){
            minn=min(minn,jp[x][i][0]);
            minn=min(minn,jp[y][i][0]);
            maxx=max(maxx,jp[x][i][1]);
            maxx=max(maxx,jp[y][i][1]);
            x=fa[x][i];y=fa[y][i];
        }
    minn=min(minn,jp[x][0][0]);
    minn=min(minn,jp[y][0][0]);
    maxx=max(maxx,jp[x][0][1]);
    maxx=max(maxx,jp[y][0][1]);
    return {minn,maxx};        
}
int main(){
    cin>>n;
    for(int i=1,x,y,z;i<n;i++)
        cin>>x>>y>>z,
        e[x].pb({y,z}),
        e[y].pb({x,z});
    jp[1][0][0]=INT_MAX;
    jp[1][0][1]=INT_MIN;
    dfs(1,1);
    cin>>q;
    while(q--){
        ll x,y;
        cin>>x>>y;
        P ans=LCA(x,y);
        cout<<ans.fi<<' '<<ans.se<<endl;
    }
    return 0;
}
/*

*/