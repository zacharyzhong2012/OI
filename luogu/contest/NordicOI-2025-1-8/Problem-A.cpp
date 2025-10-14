#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define P pair<ll,pair<ll,ll>>
using namespace std;
const ll N=1e5+9;
ll vis[N];
vector<ll>e[N];
ll n,m,k,book[N],dis[N];
priority_queue<P,vector<P>,greater<P> >que;
//means {now dis,{now pos,from which pos}}
int main(){
    cin>>n>>m>>k;
    for(int i=1,x;i<=k;i++)
        cin>>x,book[x]=1;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)
        if(book[i])
            que.push({0,{i,i}});
    for(int i=1,x,y;i<=m;i++)
        cin>>x>>y,e[x].pb(y),e[y].pb(x);
    while(!que.empty()){
        P now=que.top();que.pop();
        if(vis[now.se.fi])continue;
        vis[now.se.fi]=1;
        for(auto i:e[now.se.fi])
            if(dis[i]>now.fi+1 && i!=now.se.se){
                dis[i]=now.fi+1;
                que.push({dis[i],{i,now.se.se}});
            }
    }
    for(int i=1;i<=n;i++)
        if(dis[i]>n) cout<<"-1 ";
        else cout<<dis[i]<<' ';
    return 0;
}
/*
9 7 2
5 8
1 2
2 3
3 4
4 6
5 6
6 7 
7 8
*/