#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
using namespace std;
const ll N=1e3+9,B=131;
ll n,m,a,b;
bool num[N][N];
ull Hhash[N][N],Lhash[N][N],base[N];
int main()
{
    cin>>n>>m>>a>>b;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>num[i][j];
    for(int i=1;i<=max(n,m);i++)
        base[i]=base[i-1]*B;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            Hhash[i][j]=Hhash[i][j-1]*B+num[i][j];
            Lhash[i][j]=Lhash[i-1][j]*B+num[i][j];
        }
        
    return 0;
}