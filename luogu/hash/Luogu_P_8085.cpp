#include<bits/stdc++.h>
#define ll long long
using namespace std;
map<string,int>mp1,mp2;
const int N=1e5+9;
ll a[N],b[N],n,m,cnt,c[N];
string input;
int main()
{
    while(cin>>input)
    {
        if(input=="$") break;
        if(!mp1[input]) mp1[input]=++cnt;
        a[++n]=mp1[input];
    }
    cnt=0;
    while(cin>>input)
    {
        if(input=="$") break;
        if(!mp2[input]) mp2[input]=++cnt;
        b[++m]=mp2[input];
    }
    for(int i=1;i<=n-m+1;i++)
    {
        ll f=1;
        for(int j=1;j<=n;j++)c[j]=a[j];
        for(int j=1;j<=m;j++)a[j+i-1]-=b[j];
        for(int j=2;j<=m;j++)if(a[j+i-1]!=a[j+i-2]){f=0;break;}
        for(int j=1;j<=n;j++)a[j]=c[j];
        if(f) return cout<<i,0;
    }
    return 0;
}