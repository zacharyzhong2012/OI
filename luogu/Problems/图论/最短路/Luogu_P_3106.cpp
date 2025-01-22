#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define P pair<ll,ll>
#define mem(x,y) memset(x,y,sizeof(x));
using namespace std;
const int N=2e4+9;
ll n,m,disp[N],visp[N],disn[N];
ll disq[N],visq[N],visn[N];
struct edge{
    ll to,p,q;
};
vector<edge>e[N];
vector<P>ez[N];
inline void Dij(){
    mem(disp,0x3f);mem(disq,0x3f);
    disp[1]=0;disq[1]=0;
    priority_queue<P,vector<P>,greater<P>>que;
    que.push({0,1});
    while(!que.empty()){
        P now=que.top();que.pop();
        if(visp[now.se])continue;
        visp[now.se]=1;
        for(auto i:e[now.se])
            if(disp[i.to]>disp[now.se]+i.p){
                disp[i.to]=disp[now.se]+i.p;
                que.push({disp[i.to],i.to});
            }
    }
    que.push({0,1});
    while(!que.empty()){
        P now=que.top();que.pop();
        if(visq[now.se])continue;
        visq[now.se]=1;
        for(auto i:e[now.se])
            if(disq[i.to]>disq[now.se]+i.q){
                disq[i.to]=disq[now.se]+i.q;
                que.push({disq[i.to],i.to});
            }
    }
    
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        ll x,y,p,q;
        cin>>x>>y>>p>>q;
        e[x].pb(edge{y,p,q});
    }
    Dij();
    for(int i=1;i<=n;i++)
        for(auto j:e[i]){
            int num=0;
            if(disp[j.to]!=disp[i]+j.p)
                num++;
            if(disq[j.to]!=disq[i]+j.q)
                num++;
            ez[i].pb({j.to,num});
        }
    priority_queue<P,vector<P>,greater<P>>que;
    mem(disn,0x3f);disn[1]=0;
    que.push({0,1});
    while(!que.empty()){
        P now=que.top();que.pop();
        if(visn[now.se])continue;
        visn[now.se]=1;
        for(auto i:ez[now.se])
            if(disn[i.fi]>disn[now.se]+i.se){
                disn[i.fi]=disn[now.se]+i.se;
                que.push({disn[i.fi],i.fi});
            }
    }
    cout<<disn[n];
    return 0;
}