#include<bits/stdc++.h>
#define ll long long
using namespace std;
priority_queue<int>que;
signed main()
{
	int n;
	cin>>n;
	while(n--)
	{
		int tp;
		cin>>tp;
		if(tp==1)
		{
			int x;
			cin>>x;
			que.push(-x);
		}
		if(tp==2)
			cout<<(-que.top())<<endl;
		if(tp==3)
			que.pop();
	}
	return 0;
}