#include<algorithm>
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<climits>
#include<bitset>
#include<time.h>
#include<vector>
#include<cmath>
#define ll long long
#define pb push_back

using namespace std;
const int N=39;
ll a[N],n,m,ans;
bitset<N>c[N],num;
vector<ll>e[N];

inline ll check(){
    num=0;
    for(int i=1;i<=n;i++){
        num^=c[a[i]];
        if(num==(1ll<<n)-1)
            return i;
    }
    return n+2;
}

int main(){
    srand(32934499);

    cin>>n>>m;ans=INT_MAX;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        e[x].pb(y);
        e[y].pb(x);
    }
    for(ll i=1;i<=n;i++){
        c[i][i-1]=1;
        for(auto to:e[i]){
            c[i][to-1]=1;
        }
        a[i]=i;
    }
//    cout<<"***************\n";
    while(clock()<CLOCKS_PER_SEC*0.98){
        random_shuffle(a+1,a+n+1);
        ans=min(ans,check());
    }
    cout<<(ans>n?ans-2:ans);
    return 0;
}