#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=1e2+9;
ll n,a[N][N],c[N],cnt,color[N],num[N][2],pre[N][N],dp[N][N],vis[N];
//color is 0 or 1 to means its color
vector<int>node[N][3],ans;
inline void dfs(int x,int fa,int col){
    num[cnt][color[x]=col]++;node[cnt][col].pb(x);
    for(int i=1;i<=n;i++){
        if(i==fa || i==x || a[i][x]) continue;
        if(color[i]==-1) dfs(i,x,col^1);
        else if(color[i]==col){cout<<"No solution";exit(0);}
    }
}
int main(){
    memset(color,-1,sizeof(color));
    cin>>n;
    for(int i=1;i<=n;i++){
        int x=-1;
        while(x){
            cin>>x;
            a[i][x]=1;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(!(a[i][j] && a[j][i]) && (a[i][j] || a[j][i]))
                a[i][j]=a[j][i]=0;
    for(int i=1;i<=n;i++)
        if(color[i]==-1){
            cnt++;
            dfs(i,0,1);
        }
	dp[0][0]=1;
	for(int i=1;i<=cnt;i++)
		for(int j=n/2;j>=0;j--){
			if(j>=num[i][0] && dp[i-1][j-num[i][0]]) dp[i][j]=1,pre[i][j]=0;
			if(j>=num[i][1] && dp[i-1][j-num[i][1]]) dp[i][j]=1,pre[i][j]=1;
		}
    ll ns;
	for(int i=n/2;i>=0;i--)
		if(dp[cnt][i]){
            ns=i;
            break;
        }
    for(int i=cnt;i>=1;i--){
        if(pre[i][ns]==0){
            for(auto j:node[i][0])
                vis[j]=1,ans.pb(j);
            ns-=num[i][0];
        }else{
            for(auto j:node[i][1])
                vis[j]=1,ans.pb(j);
            ns-=num[i][1];
        }
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<' ';
    for(auto i:ans)cout<<i<<' ';
    cout<<endl;
    cout<<n-ans.size()<<' ';
    for(int i=1;i<=n;i++)
        if(!vis[i])
            cout<<i<<' ';
    return 0;
}
/*
Solution:
 1.build the Un-graph and color it
 2.count the node and use Dp solve it
 3.DFS to find it

 yl:
 5
2 3 5 0
1 4 5 3 0
1 2 5 0
1 2 3 0
4 3 2 1 0
*/