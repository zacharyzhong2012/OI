#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define P pair<int,int>
using namespace std;
const int N=1e5+9;
priority_queue<P,vector<P>,greater<P>>que;
int n,m,dis[N],vis[N],maxdis,minn,done[N];
vector<P>e[N];
inline void Dij(){
    memset(dis,0x3f,sizeof(vis));
    dis[1]=0;que.push({0,1});
    while(!que.empty()){
        P now=que.top();que.pop();
        if(vis[now.se])continue;
        vis[now.se]=1;
        for(auto i:e[now.se])
            if(dis[i.fi]>dis[now.se]+i.se){
                dis[i.fi]=dis[now.se]+i.se;
                que.push({dis[i.fi],i.fi});
            }
    }
}
inline void dfs(int x,int diss){
    if(x==n){
        if(diss!=dis[n]) maxdis=min(maxdis,diss);
        return void();
    }
    if(diss>maxdis) return;
    for(auto i:e[x]){
        if(done[i.fi]) continue;
        else{
            done[i.fi]=1;
            dfs(i.fi,diss+i.se);
            done[i.fi]=0;
        }
    }
}
int main(){
    cin>>n>>m;maxdis=INT_MAX;
    for(int i=1,x,y,z;i<=m;i++){
        cin>>x>>y>>z;
        e[x].pb({y,z});
        e[y].pb({x,z});
        if(x==n || y==n)
            maxdis=min(maxdis,z);
    }
    Dij();
    maxdis=maxdis*2+dis[n];
    dfs(1,0);
    cout<<maxdis;
    return 0;
}