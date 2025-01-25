#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=1e5+9;
ll hd[N],cnt,dfn[N],low[N],vis[N],col[N],sum[N],ct;
ll color;
stack<int>stk;
struct node{
    ll nxt,from,to,val,w;
}e[N<<1];
vector<pair<ll,ll> >vec[N];
ll n,m,dp[N];
priority_queue<pair<ll,ll> >que;
inline void add_edge(ll x,ll y,ll z,int w){
    e[++cnt]={hd[x],x,y,z,w};hd[x]=cnt;
}
inline ll dfs(int x){
    if(vis[x]) return dp[x];
    vis[x]=1;
    ll summ=0;
    for(auto i:vec[x])
        summ=max(summ,dfs(i.first)+i.second);
    dp[x]=summ+sum[x];
    return dp[x];
}
inline void tarjan(int x){
   // cout<<x<<endl;
    dfn[x]=low[x]=++ct;vis[x]=1;stk.push(x);
    for(int i=hd[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }else if(vis[v]) low[x]=min(low[x],dfn[v]);
    }
  //  cout<<x<<"  run over dfs\n";
    if(dfn[x]==low[x]){
        color++;
        int p;
        do{
            p=stk.top();
        //    cout<<p<<endl;
            stk.pop();
            col[p]=color;
            vis[p]=0;
        }while(p!=x);
    }
}
int main(){
    freopen("input.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        ll x,y,z;double w;
        cin>>x>>y>>z>>w;
        add_edge(x,y,z,w*10);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
   // cout<<"run out of Tarjan\n";
    for(int i=1;i<=m;i++){
        ll st=e[i].from,ed=e[i].to,val=e[i].val,k=e[i].w;
        if(col[st]==col[ed]){
            while(val){
                sum[col[st]]+=val;
                val=val*k/10;
            }
        }else 
            vec[col[st]].pb({col[ed],val});
       //     cout<<"build edge:"<<col[st]<<" to "<<col[ed]<<" dis is "<<val<<endl;
    }
    int st;cin>>st;
    memset(vis,0,sizeof(vis));
    cout<<dfs(col[st]);
    return 0;
}
/*
6 6
1 4 10 0.5
4 5 10 0.1
5 1 10 0.8
1 2 4 0.5
1 3 7 0.1
2 3 4 0.6
1
*/