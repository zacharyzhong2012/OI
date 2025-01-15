#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Mod=998244353;
map<ll,ll>::iterator iter;
map<ll,ll>mp;
ll n,m,k,u,v,numice,ans,sum;
int main()
{
	cin>>n>>m>>k;
	for(int i=1,x;i<=n;i++)
		cin>>x,mp[x]++,ans+=x,ans%=Mod;
	while(m--)
	{
		int x,y;
		cin>>x>>y;
		if(x<0)
		{
            while(mp.size() && (iter=mp.begin())->first+sum+x<=0)
            {
                numice-=iter->second;
                ans-=(iter->first+sum)%Mod*(iter->second);
                mp.erase(iter);
            }
            sum+=x;ans+=numice*x;
		}
		else if(x>0)
		{
            while(mp.size() && mp.rbegin()->first+sum+x>k)
            {
                numice-=iter->second;
                ans-=(iter->first+sum)%Mod*(iter->second);
                mp.erase(iter);
            }
            sum+=x;ans+=numice*x;
		}
		if(y!=0) 
        cout<<ans<<endl;
	}
    return 0;
}