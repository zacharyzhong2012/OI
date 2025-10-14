#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,m,cnt,head[N],num;
struct edge{
    int to,nxt,dfn,id;
    inline void Build(int u,int v){
        to=v;nxt=head[u];
        head[u]=id;
        return void();
    }
}e[N];
struct Decomposition{
    int fa[N],top[N],dep[N],hson[N];
    int siz[N],hedge[N],faedge[N];

    inline void dfs1(int u,int fat){
        hson[u]=-1;
        dep[u]=dep[fat]+1;
        fa[u]=fat;siz[u]=1;
        for(int i=head[u];i;i=e[i].nxt)
            if(e[i].to!=fat){
                dfs1(e[i].to,u);
                faedge[e[i].to]=i;
                siz[u]+=siz[e[i].to];
                if(siz[e[i].to]>siz[hson[u]])
                    hson[u]=e[i].to,
                    hedge[u]=i;
            }
    }

    inline void dfs2(int u,int tp){
        top[u]=tp;
        if(hson[u]!=-1)
            dfs2(hson[u],tp),
            e[hedge[u]].dfn=++num;
        for(int i=head[u];i;i=e[i].nxt)
            if(e[i].to!=fa[u] && e[i].to!=hson[u])
                dfs2(i,i),e[i].dfn=++num;
    }

    inline void Add(int u,int v){

    }
}seg;
int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        e[++cnt].id=cnt;
        e[cnt].Build(u,v);
        e[++cnt].id=cnt;
        e[cnt].Build(v,u);
    }
    seg.dfs1(1,1);
    seg.dfs2(1,1);
    while(m--){
        char op;
        int u,v;
        cin>>op>>u>>v;
        if(op=='P')
            seg.Add(u,v);
      //  else seg.query(u,v);
    }
    return 0;
}