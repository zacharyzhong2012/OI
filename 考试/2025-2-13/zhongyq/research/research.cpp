#include<algorithm>
#include<iostream>
#include<climits>
#include<cstring>
#include<cmath>
#define ll long long

using namespace std;
const int N=1e5+9;
ll n,ans[N],f,gg;
struct node{
    ll lt,rt;
}a[N];
inline bool cmp(node x,node y){
    return (x.lt==y.lt)?(x.rt<y.rt):(x.lt<y.lt);
}
inline ll abss(int x){
    return (x<0)?(-x):x;
}

inline void dfs(int x){
    if(x>n){
        f=1;
        return;
    }
    for(int i=a[x].lt;i<a[x].rt;i++){
        ll minn=N;
        for(int j=1;j<x;j++)
            minn=min(minn,abss(i-ans[j]));
        if(minn<=1) continue;
        ans[x]=i;
        dfs(x+1);
        if(f) return;
    }
}

int main(){
    freopen("research.in","r",stdin);
    freopen("research.out","w",stdout);
    int T;
    cin>>gg>>T;
    while(T--){
        cin>>n;f=0;
        for(int i=1;i<=n;i++)
           cin>>a[i].lt>>a[i].rt;
        sort(a+1,a+n+1,cmp);
        dfs(1);
        if(f==0) cout<<"-1";
        else for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
        cout<<endl;
    }

    return 0;
}