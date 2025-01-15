#include<bits/stdc++.h>
using namespace std;
const int N=1e6+9;
int n,m,fa[N];
inline int Find(int x){return (fa[x]==x)?(x):(fa[x]=Find(fa[x]));}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i;
    while(m--)
    {
        int x,y,z;
        cin>>x>>y>>z;
        if(x==1)
        {
            if(Find(y)!=Find(z))
                fa[Find(y)]=Find(z);
        }else 
        {
            if(Find(y)==Find(z))cout<<"Y\n";
            else cout<<"N\n";
        }
    }
}