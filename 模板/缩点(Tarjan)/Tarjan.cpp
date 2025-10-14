#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+9; 
int n,m,a[N],dfn[N],cnt,low[N],d[N];
int vis[N],cl[N],color,st[N],dis[N],step,siz[N];
vector<int>e[N];stack<int>stk;
inline void tarjan(int x)
{
	dfn[x]=low[x]=++step;vis[x]=1;stk.push(x);
	for(int i=0;i<e[x].size();i++)
		if(dfn[e[x][i]]==0)
			tarjan(e[x][i]),low[x]=min(low[x],low[e[x][i]]);
		else if(vis[e[x][i]]==1) low[x]=min(low[x],dfn[e[x][i]]);
	if(dfn[x]==low[x]){
		color++;
		while(stk.top()!=x){
			cl[stk.top()]=color;
			vis[stk.top()]=0;
			st[color]+=a[stk.top()];
			siz[color]++;
			stk.pop();
		}
		cl[x]=color;
		vis[x]=0;
		st[color]+=a[x];
		siz[color]++;
		stk.pop();
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1,x,y;i<=m;i++)
		cin>>x>>y,e[x].push_back(y);
	for(int i=1;i<=n;i++)
		if(dfn[i]==0)
			tarjan(i);
	int sum=0;
	for(int i=1;i<=color;i++)
	    if(siz[i]>1)
	        sum++;
	cout<<sum;
	return 0;
}