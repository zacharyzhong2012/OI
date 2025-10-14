#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=2e5+9;
ll dfn[N],low[N],n,m,a,b,cnt,f[N];
vector<int>e[N];
inline void tarjan(int x){
    dfn[x]=low[x]=++cnt;
    for(auto i:e[x]){
        if(!dfn[i]){
            tarjan(i);
            low[x]=min(low[x],low[i]);
            if(x!=a && low[i]>=dfn[x] && dfn[b]>=dfn[i]){
                f[x]=1;
            }
        }else low[x]=min(low[x],dfn[i]);
    }
}
int main(){
    cin>>n;
    while(++m){
        cin>>a>>b;
        if(a==0 && b==0) break;
        e[a].pb(b);
        e[b].pb(a);
    }
    cin>>a>>b;
    tarjan(a);
    for(int i=1;i<=n;i++)
        if(f[i]){
            cout<<i<<endl;
            return 0;
        }
    cout<<"No solution";
    return 0;
}