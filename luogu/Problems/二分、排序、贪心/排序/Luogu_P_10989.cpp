#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+9;
ll n,a[N],s[N],ans;
inline ll calc(int lt,int rt,int x){
    //from lt to rt,abs(a[i]-x);
    ll pos=upper_bound(a+lt,a+rt+1,x)-a-1;
    return (pos-lt+1)*x-(rt-pos)*x+s[rt]-2*s[pos]+s[lt-1];
}
inline ll sf(ll mid,ll x,ll y){
    ll lt=0,rt=(ll)1e9;
    while(lt+30<=rt){
        ll lpos=lt+(rt-lt)/3,lx=x+lpos;
        ll rpos=rt-(rt-lt)/3,rx=x+rpos;
        ll lp=min(2*lx-1,y);
        ll rp=min(2*rx-1,y);
        if(calc(1,mid,lx)+calc(mid+1,n,lp)<calc(1,mid,rx)+calc(mid+1,n,rp))
            rt=rpos;
        else lt=lpos;
    }
    ll minn=(ll)1e18;
    for(int i=lt;i<=rt;i++)
        minn=min(minn,calc(1,mid,x+i)+calc(mid+1,n,min(2*(x+i)-1,y)));
    return minn;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);ans=(ll)1e18;
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    for(int i=1;i<n;i++){
        ll x=a[(i+1)/2],y=a[(n-i+1)/2+i];
        if(x*2>y) ans=min(ans,calc(1,i,x)+calc(i+1,n,y));
        else ans=min(ans,sf(i,x,y));
  //      cout<<i<<' '<<x<<' '<<y<<endl;
    }
    ans=min(ans,calc(2,n,a[(n+1)/2]));
    cout<<ans;
    return 0;
}