#include<bits/stdc++.h>
using namespace std;
const int N=3e6;
string s;int nxt[N],n;
inline void sptp()
{
	for(int i=2,k=0;i<=n;i++)
	{
		while(k && s[k+1]!=s[i])
			k=nxt[k];
		if(s[k+1]==s[i])
			k++;
		nxt[i]=k;
	}
}
int main()
{
    int num=0;
    while(cin>>n)
    {
        num++;
        if(n==0)break;    
        cin>>s;
        s=' '+s;
        sptp();
        cout<<"Test case #"<<num<<endl;
        for(int i=1;i<=n;i++)
            if(nxt[i] && i%(i-nxt[i])==0)
                cout<<i<<' '<<i/(i-nxt[i])<<endl;
        cout<<endl;
    }
	return 0;
}