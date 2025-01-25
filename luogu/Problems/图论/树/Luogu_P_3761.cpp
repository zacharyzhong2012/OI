#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define P pair<ll,ll>
using namespace std;
const ll N=5e3+9;
ll n,dis,pos,vis[N],ans;
vector<P>e[N],vec[N];
map<int,int>mp[N];
inline void dfs(int x,int fa,int diss){
    if(dis<diss) dis=diss,pos=x;
    vis[x]=1;
    for(auto i:vec[x])
        if(i.fi!=fa)
            dfs(i.fi,x,diss+i.se);
}
inline ll C(ll x){return (x/2+(x%2));}
int main(){
    cin>>n;ans=INT_MAX;
    for(int i=1,x,y,z;i<n;i++)
        cin>>x>>y>>z,
        e[x].pb({y,z}),
        e[y].pb({x,z});
    for(int st=1;st<=n;st++){
        for(auto ed:e[st]){
            ll w;
            if(mp[st][ed.fi] || mp[ed.fi][st]) continue;
            mp[st][ed.fi]=mp[ed.fi][st]=1;
            memset(vis,0,sizeof(vis));
            for(int i=1;i<=n;i++)
                for(auto j:e[i])
                    if((i!=st || j.fi!=ed.fi) && (i!=ed.fi || j.fi!=st)){
                        vec[i].pb(j);
                    }else w=j.se;
            ll dis1=0,dis2=0;
            for(int i=1;i<=n;i++)
                if(!vis[i]){
                    dfs(i,i,0);
                    dfs(pos,pos,0);
                    if(!dis1){
                        dis1=dis;
                    }else{
                        dis2=dis;
                        break;
                    }
                    dis=0;pos=0;
                }
            ans=min(ans,max(max(dis1,dis2),C(dis1)+C(dis2)+w));
         //   cout<<w<<' '<<dis1<<' '<<dis2<<endl;
            for(int i=1;i<=n;i++)
                vec[i].clear();
        }
    }
    cout<<ans;
    return 0;
}