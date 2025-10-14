#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define P pair<ll,ll>
using namespace std;
const ll N=3e5+9;
ll n,m,w[N],dis[N],vis[N];
vector<P>e[N];
inline void Dij(int st){
    priority_queue<P>que;
    que.push({0,1});memset(vis,0,sizeof(vis));
    memset(dis,128,sizeof(dis));dis[1]=0;
    while(!que.empty()){
        P now=que.top();que.pop();
    //    cout<<now.se<<' '<<now.fi<<endl;
        if(vis[now.se])continue;
        vis[now.se]=1;
        for(auto i:e[now.se])
            if(dis[i.fi]<dis[now.se]+i.se){
                vis[i.fi]=0;
                dis[i.fi]=dis[now.se]+i.se;
                que.push({dis[i.fi],i.fi});
            }
    }
}
inline void Build_edge(int x,int y,int z){
    e[x].pb({y,0});
    e[x+n].pb({y+n,0});
    e[x+2*n].pb({y+2*n,0});
    if(z==2){
        e[x].pb({y,0});
        e[x+n].pb({y+n,0});
        e[x+2*n].pb({y+2*n,0});
        swap(x,y);
        e[x].pb({y,0});
        e[x+n].pb({y+n,0});
        e[x+2*n].pb({y+2*n,0});
    }
    return void();
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>w[i];
    // build edge(in the same height)
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        Build_edge(x,y,z);
    }

    //build edge(i to i+n)
    for(int i=1;i<=n;i++){
        e[i].pb({i+n,-w[i]});
        e[i+n].pb({i+2*n,w[i]});
    }

    //Run dij:
    Dij(1);

    //output
    cout<<dis[3*n];
    return 0;
}