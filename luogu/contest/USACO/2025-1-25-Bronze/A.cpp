#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int T,vis[N][N],a,b,n,num[N][N],sum;
int main(){
    cin>>T;
    while(T--){
        sum=0;
        cin>>n>>a>>b;swap(a,b);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                char s;
                cin>>s;
                if(s=='W') num[i][j]=0;
                if(s=='G') num[i][j]=1;
                if(s=='B') num[i][j]=2;
                vis[i][j]=0;
            }
        int f=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                // cout<<vis[i][j]<<' '<<num[i][j]<<' '<<i<<' '<<j<<endl;
                if(vis[i][j]<num[i][j]){
                    sum++;
                    vis[i][j]++;
                    if(num[i+a][j+b]!=0) 
                        vis[i+a][j+b]++;
                }
                if(vis[i][j]>num[i][j] || vis[i][j]<num[i][j]){
                    f=1;
                    break;
                }
            }
            if(f)break;
        }
        if(!f) cout<<sum<<endl;
        else cout<<"-1\n";
    }
    return 0;
}