#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Len=1e6+9;
ll nxt[Len],ans[Len],n,m;
string a,b;
inline void KMP()
{
    for(int i=2,j=0;i<=m;i++)
    {
        while(j>0 && b[j+1]!=b[i]) j=nxt[j];
        if(b[j+1]==b[i]) nxt[i]=++j;
    }
    for(int i=1,j=0;i<=n;i++)
    {
        while(j>0 && (j==n || a[i]!=b[j+1])) j=nxt[j];
        if(b[j+1]==a[i]) j++;
        if(j==m)
            cout<<i-m+1<<endl; 
    }
}
int main()
{
    cin>>a>>b;
    a=' '+a;n=a.size()-1;
    b=' '+b;m=b.size()-1;
    KMP();
    for(int i=1;i<=m;i++)
        cout<<nxt[i]<<' ';
    return 0;
}