#include<bits/stdc++.h>
#define ll long long
#define lb(x) ((x)&(-x))
using namespace std;
const ll N=2e6+9;
ll n,a[N],tr[N];
inline void add(ll x,ll y){for(x;x<N;x+=lb(x))tr[x]+=y;}
inline ll query(ll x){ll sum=0;for(x;x;x-=lb(x))sum+=tr[x];return sum;}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    add(a[1],1);
    for(int i=2;i<=n;i++)
    {
        ll lt=a[i],rt=N,ans;
        while(lt<=rt)
        {
            ll mid=lt+rt>>1;
         //   cout<<lt<<' '<<rt<<' '<<mid<<' '<<query(mid)<<' '<<query(a[i]-1)<<endl;
            if(query(mid)-query(a[i]-1)<=mid-a[i])rt=mid-1,ans=mid;
            else lt=mid+1;
        }
        a[i]=ans;
        add(ans,1);
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
}