#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cmath>
#define ll long long
#define mem(a) memset(a,0,sizeof(a))

using namespace std;
const ll Mod=998244353ll,N=3;
ll b,d,n;

struct Mat{
    ll a[N][N],n,m;

    friend inline Mat operator *(const Mat &x,const Mat &y){
        Mat ans;mem(ans.a);
        
        for(int i=1;i<=x.n;i++)
            for(int j=1;j<=y.m;j++)
                for(int k=1;k<=x.m;k++)
                    ans.a[i][j]=(ans.a[i][j]+x.a[i][k]*y.a[k][j]%Mod)%Mod;
        ans.n=x.n;ans.m=y.m;
        return ans;
    }   
}ans,gc;
inline Mat ksm(Mat x,ll y){
    Mat tmp;mem(tmp.a);tmp.n=x.n;tmp.m=x.m;
    for(int i=1;i<=x.n;i++)tmp.a[i][i]=1;
    
    while(y){
        if(y&1) tmp=tmp*x;
        x=x*x;y>>=1;
    }
    
    return tmp;
}

int main(){
    int T;cin>>T;d=5,b=1;
    while(T--){
        cin>>n;
        if(n==0) return cout<<1,0;ans.n=2,ans.m=1;
        ll x=b,y=(d-b*b)/4ll;gc.n=2;gc.m=2;
        mem(gc.a);mem(ans.a);
        gc.a[1][1]=x;gc.a[1][2]=y;gc.a[2][1]=1;
        ans.a[1][1]=b;ans.a[2][1]=2;gc=ksm(gc,n-1)*ans;
        ll tmpans=gc.a[1][1];
        if(n%2==1) tmpans++;
        if(tmpans<0) tmpans+=Mod;
        cout<<tmpans%Mod<<endl;
    }
    return 0;
}

/*
f[n]=b*f[n-1]+(d-b*b)/4*f[n-2];
f[0]=2;f[1]=b;
*/