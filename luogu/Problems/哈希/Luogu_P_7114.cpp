#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e6+9,M=139,Mod=1e9+7;
ll n,hz[N],book[1000],qz[N],qzh[N],sum,hs[N],base[N];
string s;
inline void init()
{
	n=s.size();s=' '+s;
    memset(book,0,sizeof(book));
	for(int i=0;i<=n+1;i++)hz[i]=qzh[i]=0;
	for(int i=0;i<=26;i++)qz[i]=0;
	sum=0;
}
inline void inithash()
{
	base[0]=1;
	for(int i=1;i<=n;i++)base[i]=base[i-1]*M%Mod;
	for(int i=1;i<=n;i++)
	{
		hs[i]=(hs[i-1]*M%Mod+s[i])%Mod;
		while(hs[i]<0)hs[i]+=Mod;
	}
}
inline ll ksm(ll x,ll y)
{
    ll sum=1;
    while(y)
    {
        if(x&1)sum=sum*x%Mod;
        x=x*x%Mod;y>>=1;
    }
    return sum;
}
inline ll geths(ll lt,ll rt)
{
    ll num=(hs[rt]-hs[lt-1]*base[rt-lt+1]%Mod+Mod)%Mod;
    while(num<0)num+=Mod;return num;
}
inline void solve()
{
	cin>>s;
	init();
		
	for(int i=n;i>=1;i--)hz[i]=hz[i+1]+(((++book[s[i]])%2==0)?(-1):(1));
	memset(book,0,sizeof(book));
	for(int i=1;i<=n;i++)qzh[i]=qzh[i-1]+(((++book[s[i]])%2==0)?(-1):(1));
    inithash();
	//cl
	for(int i=2;i<=n;i++)
    {
		for(int j=qzh[i-1];j<=26;j++)qz[j]++;
        ll tmp=0,j,num=0;
        for(j=1;j+i-1<n;j+=i)
			if(geths(1,i)==geths(j,j+i-1)) 
				num+=qz[26]-qz[hz[j+i]],tmp++;
            else break;
		sum+=(tmp*(i-1)-num);
    }
	cout<<sum<<endl;
}
int main()
{
	int T;cin>>T;
	while(T--){solve();}
	return 0;
}