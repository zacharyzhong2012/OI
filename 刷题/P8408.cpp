#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cmath>
#define ll long long
#define mem(a) memset(a,0x3f,sizeof(a));

using namespace std;
const ll N=109;
ll n,t,ans,tmpnum[N*10];

struct Mat{
    ll a[N][N];

    friend inline Mat operator *(const Mat &x,const Mat &y){
        Mat z;mem(z.a);

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++)
                    z.a[i][j]=min(z.a[i][j],x.a[i][k]+y.a[k][j]);
        return z;
    } 
}A,B,pw[N];

inline bool check(Mat x){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(x.a[i][j]<=t) 
                return 1;
    return 0;
}

int main(){
    cin>>n>>t;

    mem(A.a);
    for(int i=1;i<=n;i++){
        ll num,times;
        cin>>num>>times;
        for(int j=1;j<=num;j++){
            cin>>tmpnum[j];
        }
        for(int j=1;j<=num;j++){
            ll tmpppp;
            cin>>tmpppp;
            A.a[i][tmpnum[j]]=min(A.a[i][tmpnum[j]],times+tmpppp);
        }
    }
    pw[0]=A;
    for(int i=1;i<=50;i++)
        pw[i]=pw[i-1]*pw[i-1];
    for(int i=50;i>=0;i--)
        if(check(B*pw[i])){
            ans+=(1ll<<i);
            B=B*pw[i];
        }
    cout<<ans;
    return 0;
}
