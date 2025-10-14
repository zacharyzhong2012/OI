#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cmath>
#include<queue>
#include<map>
#define ll long long
#define P pair<ll,ll>
#define fi first
#define se second

using namespace std;
const int N=1e6+9;
ll n,m,book1[N],book2[N],cnt,ans[N<<2][4];
P a[N],b[N];
inline void add(int x,int y,int z,int t){
    ++cnt;
    ans[cnt][0]=x;
    ans[cnt][1]=y;
    ans[cnt][2]=z;
    ans[cnt][3]=t;
    return;
}

int main(){
    freopen("super.in","r",stdin);
    freopen("super.out","w",stdout);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        ll x,y;
        cin>>x>>y;
        book1[x]++;
        book1[y]++;
        a[i]={x,y};
    }
    for(int i=1;i<=m;i++){
        ll x,y;
        cin>>x>>y;
        book2[x]++;
        book2[y]++;
        b[i]={x,y};
    }
    ll pd=1;
    for(int i=1;i<=n;i++)
        if(book1[i]!=book2[i]){
            pd=0;
            break;
        }

    if(m==2){
        if((b[1].fi==a[1].fi && b[1].se==a[2].se) || (b[1].fi==a[2].se && b[1].se==a[1].fi)){
            pd=0;
        }else pd=1;
    }

    if(pd) cout<<"YES\n";
    else return cout<<"NO",0;
    cout<<0;
    return 0;
}