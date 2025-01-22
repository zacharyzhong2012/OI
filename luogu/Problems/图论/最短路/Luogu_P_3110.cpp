#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define Pp pair<int,int>
#define mem(x) memset(x,0x3f,sizeof(x))
using namespace std;
const int N=8e4+9;
int dis1[N],dis2[N],B,E,P,n,m,disn[N];
int vis1[N],vis2[N],visn[N];
vector<int>e[N];
inline void Dij(int dis[],int vis[],int num,int st){
    priority_queue<Pp,vector<Pp>,greater<Pp>>que;
    dis[st]=0;que.push({0,st});
    while(!que.empty()){
        Pp now=que.top();que.pop();
        if(vis[now.se])continue;
        vis[now.se]=1;
        for(auto i:e[now.se])
            if(dis[i]>dis[now.se]+num){
                dis[i]=dis[now.se]+num;
                que.push({dis[i],i});
            }
    }
}
int main(){
    cin>>B>>E>>P>>n>>m;
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y;
        e[x].pb(y);
        e[y].pb(x);
    }
    mem(dis1);mem(dis2);mem(disn);
    Dij(dis1,vis1,B,1);
    Dij(dis2,vis2,E,2);
    Dij(disn,visn,P,n);
    int minn=dis2[n]+dis1[n];
//    for(int i=1;i<=n;i++)cout<<dis1[i]<<' ';cout<<endl;
//    for(int i=1;i<=n;i++)cout<<dis2[i]<<' ';cout<<endl;
//    for(int i=1;i<=n;i++)cout<<disn[i]<<' ';cout<<endl;
    for(int i=1;i<=n;i++)
        minn=min(minn,disn[i]+dis1[i]+dis2[i]);
    cout<<minn;
    return 0;
}