#include<algorithm>
#include<iostream>
#include<climits>
#include<cmath>

#define P pair<int,int>
#define se second
#define fi first

using namespace std;
const int N=2e6,MX=22;
int n,k,pos,dis[N][25],maxx,ans;
P num[N];

int main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++){
        cin>>num[i].fi>>num[i].se;
        if(num[i].se<num[i].fi)
            num[i].se+=n;
    }
    sort(num+1,num+k+1);

    pos=1;ans=INT_MAX;
    for(int i=1;i<=n;i++){
        while(pos<=k && num[pos].fi<=i)
            maxx=max(maxx,num[pos].se+1),pos++;
        dis[i][0]=maxx;
    }
    for(int i=1;i<=MX;i++)
        for(int j=1;j<=2*n;j++)
            dis[j][i]=dis[dis[j][i-1]][i-1];

    for(int i=1;i<=2*n;i++){
        pos=i;int sum=0;
        for(int j=MX;j>=0;j--)
            if(dis[pos][j]<n+i){
                pos=dis[pos][j];
                sum+=(1<<j);
            }
        pos=dis[pos][0];sum++;
        if(pos>=n+i) ans=min(ans,sum);
    }
    if(ans>n) cout<<"impossible\n";
    else cout<<ans;
    return 0;
}