#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define mem(x) memset(x,0,sizeof(x))
using namespace std;
const ll N=2e5+9;
ll cnt,n,num,root;
vector<ll>ans[N];
struct Decomposition{
    ll fa[N],dfn[N],top[N],siz[N],hson[N];
    vector<ll>e[N];
    inline void dfs1(ll u){
        hson[u]=-1;
    //    cout<<u<<endl;
        siz[u]=1;
        for(auto i:e[u]){
            dfs1(i);siz[u]+=siz[i];
            if(siz[i]>siz[hson[u]])
                hson[u]=i;
        }
    }
    inline void dfs2(ll u,ll tp){
        dfn[u]=++cnt;top[u]=tp;ans[tp].pb(u);
        if(hson[u]!=-1)dfs2(hson[u],tp);
        for(auto i:e[u])
            if(i!=hson[u] && i!=fa[u])
                dfs2(i,i);
    }
}seg;
inline void solve(){
    cin>>n;num=0;cnt=0;
    for(int i=1;i<=n;i++)
		ans[i].clear(),
		seg.e[i].clear();
    for(int i=1;i<=n;i++)
    {
        cin>>seg.fa[i];
        if(seg.fa[i]==i)
			root=i;
        else seg.e[seg.fa[i]].pb(i);
	}
    seg.dfs1(root);
    seg.dfs2(root,root);
    for(int i=1;i<=n;i++)
    	if(ans[i].size())
    		num++;
    cout<<num<<endl;
    for(int i=1;i<=n;i++)
        if(ans[i].size()){
            cout<<ans[i].size()<<endl;
            for(auto j:ans[i])
                cout<<j<<' ';
            cout<<endl;
        }
    cout<<endl;
}
int main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}