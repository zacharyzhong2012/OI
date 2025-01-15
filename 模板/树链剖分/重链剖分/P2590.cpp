/*
solve on 2025/1/15 16:46:49
contain the problem in P2590
also can get LCA use seg.LCA(x,y)

author:zacharyzhong,luogu:z_yq,UID:669171
*/
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define pb push_back
#define lson(x) x<<1
#define P pair<ll,ll>
#define rson(x) x<<1|1
#define mid(x,y) ((x+y)>>1)
using namespace std;
const ll N=3e4+9;
ll n,m,s,cnt,w[N];
inline P cg(int x,int y){return {min(x,y),max(x,y)};}
struct Tree{
    ll sum[N<<2],lt[N<<2],rt[N<<2],mx[N<<2];
    inline void push_up(int id){
        sum[id]=sum[lson(id)]+sum[rson(id)];
        mx[id]=max(mx[lson(id)],mx[rson(id)]);
        return void();
    }
    inline void build(int id,int l,int r){
        lt[id]=l;rt[id]=r;
        if(l==r){mx[id]=sum[id]=w[l];return void();}
        build(lson(id),l,mid(l,r));
        build(rson(id),mid(l,r)+1,r);
        push_up(id);
    }
    inline void change(int id,int pos,int k){
        if(lt[id]==pos && rt[id]==pos)return sum[id]=mx[id]=k,void();
        if(pos<=mid(lt[id],rt[id]))
            change(lson(id),pos,k);
        else change(rson(id),pos,k);
        push_up(id);
    }
    inline ll querysum(int id,P pos){
        if(lt[id]>=pos.fi && pos.se>=rt[id]) return sum[id];
        ll tmpsum=0;
        if(pos.fi<=mid(lt[id],rt[id]))
            tmpsum+=querysum(lson(id),pos);
        if(pos.se>mid(lt[id],rt[id]))
            tmpsum+=querysum(rson(id),pos);
        return tmpsum;
    }
    inline ll querymax(int id,P pos){
        if(lt[id]>=pos.fi && pos.se>=rt[id]) return mx[id];
        ll tmpmax=INT_MIN;
        if(pos.fi<=mid(lt[id],rt[id]))
            tmpmax=max(tmpmax,querymax(lson(id),pos));
        if(pos.se>mid(lt[id],rt[id]))
            tmpmax=max(tmpmax,querymax(rson(id),pos));
        return tmpmax;
    }
}tree;
struct Decomposition{
    ll top[N],fa[N],hson[N],siz[N];
    ll dep[N],dfn[N];
    vector<ll>to[N];          
    inline void dfs1(int x,int fat){
        dep[x]=dep[fat]+1;
        siz[x]=1;fa[x]=fat;
        for(auto i:to[x])
            if(i!=fat){
                dfs1(i,x);
                siz[x]+=siz[i];
                if(siz[hson[x]]<siz[i])
                    hson[x]=i;
            }
        if(hson[x]==0) hson[x]=-1;
    }
    inline void dfs2(int x,int tp){
        top[x]=tp;dfn[x]=++cnt;
        if(hson[x]!=-1) dfs2(hson[x],tp);
        for(auto i:to[x])
            if(i!=fa[x] && i!=hson[x])
                dfs2(i,i);
    }
    inline ll LCA(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]])
                x=fa[top[x]];
            else y=fa[top[y]];
        }
        return ((dep[x]>dep[y])?y:x);
    }
    inline ll Findmax(int x,int y){
        ll maxx=INT_MIN;
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]]){
                maxx=max(maxx,tree.querymax(1,cg(dfn[x],dfn[top[x]])));
                x=fa[top[x]];
            }else{
                maxx=max(maxx,tree.querymax(1,cg(dfn[y],dfn[top[y]])));
                y=fa[top[y]];
            }
        }
        maxx=max(maxx,tree.querymax(1,cg(dfn[x],dfn[y])));
        return maxx;
    }
    inline ll getsum(int x,int y){
        ll sum=0;
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]]){
                sum+=tree.querysum(1,cg(dfn[x],dfn[top[x]]));
                x=fa[top[x]];
            }else{
                sum+=tree.querysum(1,cg(dfn[y],dfn[top[y]]));
                y=fa[top[y]];
            }
        }
        sum+=tree.querysum(1,cg(dfn[x],dfn[y]));
        return sum;
    }
}seg;
int main(){
    cin>>n;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,
        seg.to[x].pb(y),
        seg.to[y].pb(x);
    seg.dfs1(1,1);seg.dfs2(1,1);
    for(int i=1;i<=n;i++)
        cin>>w[seg.dfn[i]];
    tree.build(1,1,n);
    ll q;cin>>q;
    while(q--)
    {
        string s;
        cin>>s;
        if(s=="CHANGE"){
            ll u,t;
            cin>>u>>t;
            tree.change(1,seg.dfn[u],t);
        }else if(s=="QMAX"){
            ll u,v;
            cin>>u>>v;
            cout<<seg.Findmax(u,v)<<endl;
        }else{
            ll u,v;
            cin>>u>>v;
            cout<<seg.getsum(u,v)<<endl;
        }
    }
    return 0;
}