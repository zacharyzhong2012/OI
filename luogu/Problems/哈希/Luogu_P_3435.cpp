#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Len=1e6+9;
ll nxt[Len],n,sum;
string a;
inline void KMP()
{
    for(int i=2,j=0;i<=n;i++)
    {
        while(j && a[i]!=a[j+1]) j=nxt[j];
        j+=(a[i]==a[j+1]);nxt[i]=j;
    }
    for(int i=2,j=2;i<=n;i++)
    {
        j=i;
        while(nxt[j]) j=nxt[j];
        if(nxt[i])nxt[i]=j;
        sum+=i-j;
    }
}
int main()
{
    cin>>n>>a;a=' '+a;
    KMP();cout<<sum;
    return 0;
}