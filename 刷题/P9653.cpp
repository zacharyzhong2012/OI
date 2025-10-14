#include<algorithm>
#include<iostream>
#include<climits>
#include<cstring>
#include<cmath>
#define ll long long

using namespace std;
const int N=5e5+9;
int n,m,k,a[N],sum,jjj;

inline void solve(){
    cin>>n>>m>>k;jjj=-1;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;m&&i<=n-2;i++)
        if(a[i]==a[i+1] && a[i+1]==a[i+2]){
            a[i+1]=--jjj;
            m--;
        }
    for(int i=1;m&&i<=n-1;i++)
        if(a[i]==a[i+1]){
            a[i]=--jjj;
            m--;
        }
    sum=1;
    for(int i=2;i<=n;i++)
        if(a[i]!=a[i-1])
            sum++;
    cout<<sum<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}