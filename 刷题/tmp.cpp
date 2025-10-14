#include<bits/stdc++.h>
#define P pair<int,int>
#define ll long long
#define pb push_back
#define se second
#define fi first

using namespace std;
const int N=79,M=2e5+9;
int n,m,k,dis[N][N],posx,posy;
int e,tmax,f[N],jd[N],ans,Pos[N],dp[N];
struct node{
    ll pgi,pos,t;
}num[M];

inline bool cmp(node x,node y){
    return x.t<y.t;
}
inline int  check(){
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=1;i<=k;i++)
        Pos[jd[i]]=i;
    for(int i=1;i<=e;i++){
        if(Pos[num[i].pgi]==1)
            dp[i]=1;
        for(int j=1;j<i && !dp[i];j++)
            if(Pos[num[j].pgi]==Pos[num[i].pgi]-1)
                dp[i]|=(dp[j] && (dis[num[j].pos][num[i].pos]<=num[i].t-num[j].t));
        cout<<i<<' '<<dp[i]<<endl;
        if(Pos[num[i].pgi]==k && dp[i]==1)
            return cout<<endl,num[i].t;
    }
    cout<<endl;
    return INT_MAX;
}       
int main(){
    srand(time(0));
    cin>>n>>m>>k;ans=INT_MAX;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)dis[i][i]=0;

    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=min(dis[v][u],w);
    }

    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

    cin>>e>>tmax;
    for(int i=1;i<=e;i++){
        int p,x,t;
        cin>>p>>x>>t;
        num[i]={p,x,t};
    }
    sort(num+1,num+e,cmp);
    cin>>posx>>posy;

    for(int i=1;i<=k;i++)jd[i]=i;
    while(clock()<CLOCKS_PER_SEC*0.95){
        random_shuffle(jd+1,jd+k+1);
        ans=min(ans,check());
    }
    if(ans==INT_MAX) cout<<-1;
    else cout<<ans;
    return 0;
}

