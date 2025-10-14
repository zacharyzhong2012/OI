#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+9;
ll fa[N],n,m;
inline ll Find(int x){return (x==fa[x])?(x):(fa[x]=Find(fa[x]));}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n*2;i++)fa[i]=i;
    while(m--)
    {
        char c;
        cin>>c;
        if(c=='R')
        {
            ll x,y;
            cin>>x>>y;
            if(Find(x)!=Find(y))
                fa[Find(x)]=Find(y),
                fa[Find(x+n)]=Find(y+n);
        }else if(c=='A')
        {
            ll x,y;
            cin>>x>>y;
            if(Find(x)!=Find(y+n))
                fa[Find(x)]=Find(y+n),
                fa[Find(x+n)]=Find(y);
        }
        else
        {
            ll x,y;
            cin>>x>>y;
            if(Find(x)==Find(y)) cout<<"R\n";
            else if(Find(x)==Find(y+n)) cout<<"A\n";
            else cout<<"?\n";
        }
    }
    return 0;
}
/*
4 5
R 1 2
A 2 3
A 1 4
Q 2 4
Q 1 3
*/