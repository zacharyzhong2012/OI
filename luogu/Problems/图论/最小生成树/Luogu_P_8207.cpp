#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=5e6+9;
ll l,r,ans,fa[N],cnt;
struct node{
    ll st,ed,w;
}e[N];
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline ll lcm(ll x,ll y){return x*y/gcd(x,y);}
inline ll cmp(node x,node y){return x.w<y.w;}
inline ll Find(ll x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void merge(ll x,ll y){
    fa[min(Find(x),Find(y))]=max(Find(x),Find(y));
}
int main(){
    cin>>l>>r;
    for(int i=2;i<=r;i++){
        ll lst=i*(l/i+(l%i!=0));
        for(int st=i*(l/i+(l%i!=0)+1);st<=r;st+=i)
            e[++cnt]={lst,st,lcm(lst,st)};
        if(i>=l) e[++cnt]={lst,l,lcm(lst,l)};
    }
    for(int i=l;i<=r;i++) fa[i]=i;
    ll sum=0;
    sort(e+1,e+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        if(Find(e[i].st)!=Find(e[i].ed))
            merge(e[i].st,e[i].ed),
            ans+=e[i].w,sum++;
        if(sum==r-l) break;
    }
    cout<<ans;
    return 0;
}