#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=809;
struct node{ll s,t,w;}e[N*N];
ll gx[9]={0,1},gy[9]={1,0},cnt;
ll n,m,t,a[N][N],num[N][N],v[N*N],fa[N*N],siz[N*N];
inline int change(ll x,ll y){return (x-1)*m+y;}
inline int cmp(node x,node y){return x.w<y.w;}
inline int Find(ll x){if(fa[x]==x)return x;return fa[x]=Find(fa[x]);}
int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            num[i][j]=change(i,j);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            int flag;
            cin>>flag;
            v[num[i][j]]=flag;
            fa[num[i][j]]=num[i][j];
            siz[num[i][j]]=1;
            for(int k=0;k<=1;k++)
            {
                int nx=i+gx[k],ny=j+gy[k];
                if(nx<1 || nx>n || ny<1 || ny>m) continue;
                e[++cnt]={num[i][j],num[nx][ny],abs(a[i][j]-a[nx][ny])};
            }
        }
    sort(e+1,e+cnt+1,cmp);
    ll ans=0;
    for(int i=1;i<=cnt;i++)
    {
        ll fax=Find(e[i].s),fay=Find(e[i].t);
        if(fax==fay) continue;
        if(siz[fax]+siz[fay]>=t)
        {
            if(siz[fax]<t) ans+=v[fax]*e[i].w;
            if(siz[fay]<t) ans+=v[fay]*e[i].w;
        }
        if(siz[fax]>siz[fay]) swap(fax,fay);
        fa[fax]=fay;siz[fay]+=siz[fax];v[fay]+=v[fax];
    }
    cout<<ans;
    return 0;
}