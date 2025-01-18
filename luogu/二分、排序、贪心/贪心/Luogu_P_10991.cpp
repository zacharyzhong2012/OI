#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+9;
ll n,p,q,a[N],minn,ans,maxx;
priority_queue<ll>que;
priority_queue<ll,vector<ll>,greater<ll>>quee;
int main(){
    cin>>n>>p>>q;minn=INT_MAX;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=p;i<=n;i++){
        minn=min(minn,a[i]);
        que.push(a[i]);
        if(que.size()>q-p+1){
            que.pop();
            ans=max(ans,que.top()-minn);
        }
    }
    for(int i=q;i>=1;i--){
        maxx=max(maxx,a[i]);
        quee.push(a[i]);
        if(quee.size()>q-p+1){
            quee.pop();
            ans=max(ans,maxx-quee.top());
        }
    }
    cout<<ans;
    return 0;
}