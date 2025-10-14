
#include<iostream>
#include<cstring>
#define fi first
#define se second
#define ll long long
#define P pair<ll,ll>
using namespace std;
const ll N=55;
ll n,e[N][N],to[N],vis[N],To[N];
struct page{
    ll x,y,xx,yy;
}a[N];
inline bool match(int x){
    for(int i=n+1;i<=2*n;i++)
        if(e[x][i] && !vis[i]){
            vis[i]=1;
            if(!to[i] || match(to[i]))
                return to[i]=x,1;
        }
    return 0;
}
inline void solve(int T){
    memset(e,0,sizeof(e));
    memset(vis,0,sizeof(vis));
    memset(to,0,sizeof(to));
    memset(To,0,sizeof(To));
    if(n==0) exit(0);
    cout<<"Heap "<<T<<endl;
    for(int i=1;i<=n;i++)
        cin>>a[i].x>>a[i].xx>>a[i].y>>a[i].yy;
    for(int i=1;i<=n;i++){
        ll x,y;
        cin>>x>>y;
        for(int j=1;j<=n;j++)
            if(a[j].x<=x && a[j].xx>=x && a[j].y<=y && a[j].yy>=y){
                e[i][j+n]=1;
                // cout<<i<<' '<<j<<endl;
            }
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(match(i))
            ans++;
    }
    if(ans!=n){
        cout<<"none\n\n";
        return void();
    }
    for(int i=1;i<=n;i++)To[i]=to[i+n];
    //for(int i=n+1;i<=2*n;i++)cout<<to[i]<<' ';
    //cout<<endl;
    for(int i=1;i<=n;i++){
        memset(to,0,sizeof(to));
        e[To[i]][i+n]=0;
        ll pans=0;
        for(int i=1;i<=n;i++)
        {
            memset(vis,0,sizeof(vis));
            if(match(i))
                pans++;
        }
        //cout<<i<<' '<<pans<<endl;
        if(pans==n){
            cout<<"none\n\n";
            return void();
        }
        e[To[i]][i+n]=1;
    }
    for(int i=1;i<=n;i++)
        cout<<"("<<char(i+'A'-1)<<", "<<To[i]<<") ";
    cout<<endl<<endl;
}
int main(){
    freopen("tmp.in","r",stdin);
    int T=0;
    while(cin>>n){solve(++T);}
    return 0;
}