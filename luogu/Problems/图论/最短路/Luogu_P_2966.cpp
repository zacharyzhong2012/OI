#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=259;
struct node{ll id,num;}a[N];
ll n,m,q,dis[N][N],dist[N][N];
inline bool cmp(node x,node y){
    return x.num<y.num;
}
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i].num,a[i].id=i;
    sort(a+1,a+n+1,cmp);
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)dis[i][i]=0;
    memset(dist,0x3f,sizeof(dist));
    for(int i=1;i<=m;i++){
        ll u,v,w;cin>>u>>v>>w;
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=min(dis[v][u],w);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                ll u=a[i].id,v=a[j].id,w=a[k].id;
                dis[u][v]=min(dis[u][v],dis[u][w]+dis[w][v]);
                dist[u][v]=min(dist[u][v],dis[u][v]+max(a[i].num,max(a[j].num,a[k].num)));
            }
        }
    }
    while(q--){
        ll u,v;
        cin>>u>>v;
        cout<<dist[u][v]<<endl;
    }
    return 0;
}