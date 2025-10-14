#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Mod=1e9+7,N=309;
ll T,n,q,a[N],b[N],ans[N][N];
inline ll mul(ll x,ll y,ll p){
    ll t=x*y-(ll)((long double)x/p*y+1.0e-8)*p;
    return (t<0)?t+p:t;
}
inline ll gcd(ll x,ll y){
    return y?gcd(y,x%y):x;
}
inline void solve(ll lt,ll rt){
    if(lt==rt) return ans[lt][rt]=a[lt],void();
    ll mid=(lt+rt)>>1;
    solve(lt,mid),solve(mid+1,rt);
    
}
int main(){
    cin>>T;
    while(T--)
    {
        cin>>n>>q;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        solve(1,n);
        while(q--)
        {
            ll l,r;
            cin>>l>>r;
            cout<<ans[l][r]<<endl;
        }
    }
    return 0;
}