#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+9;
int n,m,hd[N],cnt,dep[N],tsum[N],fa[N][25],middd,mx;
ll sum[N][25],qz[N];
struct edge{
    int nxt,to,w;
}e[N<<1];
struct node{
    int lt,rt;ll sum;int Lca;
    bool operator <(const node &y)const{
        return this->sum<y.sum;
    }
}dis[N];
inline void add_edge(int x,int y,int z){
    e[++cnt]={hd[x],y,z};hd[x]=cnt;
}
inline void dfs(int x,int F){
    fa[x][0]=F;dep[x]=dep[F]+1;
    for(int i=1;i<=24;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1],
        sum[x][i]=sum[x][i-1]+sum[fa[x][i-1]][i-1];
    for(int i=hd[x];i;i=e[i].nxt){
        if(e[i].to==F) continue;
        qz[e[i].to]=qz[x]+e[i].w;
        sum[e[i].to][0]=e[i].w;
        dfs(e[i].to,x);
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=24;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y]) 
            x=fa[x][i];
    if(x==y) return x;
    for(int i=24;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
inline void Dfs(int x,int F){
 //   cout<<x<<' '<<F<<endl;
    for(int i=hd[x];i;i=e[i].nxt){
        if(e[i].to==F) continue;
        Dfs(e[i].to,x);
        tsum[x]+=tsum[e[i].to];
    }
}
inline bool check(){
    int posl=1,posr=m,ans,num=0,x=middd;
    while(posl<=posr){
        int mid=posl+posr>>1;
        if(dis[mid].sum>x) ans=mid,posr=mid-1;
        else posl=mid+1;
    }
    //求出ans,意味着ans~m的所有路径均超出了预算
    //接下来要差分求出所有的路径都有的一条边，并计算
    for(int i=ans;i<=m;i++){
        num++;
        tsum[dis[i].Lca]-=2;
        tsum[dis[i].lt]++;
        tsum[dis[i].rt]++;
    }
    Dfs(1,1);
    ll maxx=INT_MIN;
    for(int i=2;i<=n;i++){
        if(tsum[i]==num){
            maxx=max(maxx,qz[i]-qz[fa[i][0]]);
        }
        tsum[i]=0;
    }
    //cout<<x<<' '<<maxx<<endl;
    if(dis[m].sum-maxx<=x) return 1;
    return 0;
}
int main(){
   // freopen("input.in","r",stdin);

    cin>>n>>m;
    for(int i=1;i<n;i++){
        int x,y,z;
        cin>>x>>y>>z;
        add_edge(x,y,z);
        add_edge(y,x,z);
        mx=max(mx,z);
    }
    dfs(1,1);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        int lca=LCA(x,y);
        dis[i]={x,y,qz[x]-qz[lca]+qz[y]-qz[lca],lca};  
    }
    sort(dis+1,dis+m+1);
    ll lt=max(1ll,dis[m].sum-mx),rt=dis[m].sum-1,ans=dis[m].sum;
    while(lt<=rt){
        middd=lt+rt>>1ll;
        if(check()) ans=middd,rt=middd-1;
        else lt=middd+1;
    }
    cout<<ans;
    return 0;
}