#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e6+9;
ll n,a[N],b[N];
inline bool check(int x){
    for(int i=1;i<x;i++)b[i]=a[i];
    sort(b+1,b+x);
    ll tmp=n-x;
    for(int i=1;i<x;i++)
        if(b[i]>tmp) return 0;
        else tmp++;
    return 1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    ll lt=1,rt=n,ans;
    while(lt<=rt){
        ll mid=lt+rt>>1;
        if(check(mid)) lt=mid+1,ans=mid;
        else rt=mid-1;
    }
    cout<<n-ans;
    return 0;
}
//记录：31字符每行