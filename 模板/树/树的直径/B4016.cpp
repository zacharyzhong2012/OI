#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const ll N=1e6+9;
ll n,dis,pos;
vector<ll>e[N];
inline void dfs(int x,int fa,int diss){
    if(dis<diss) dis=diss,pos=x;
    for(auto i:e[x])if(i!=fa)dfs(i,x,diss+1);
}
int main(){
    cin>>n;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,
        e[x].pb(y),
        e[y].pb(x);
    dfs(1,1,0);dfs(pos,pos,0);
    cout<<dis;
    return 0;
}