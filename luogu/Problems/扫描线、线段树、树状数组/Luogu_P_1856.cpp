#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=8e5+9,M=4e5+9;
struct node1{ll x,y,yy,flag;}a[N];
struct node2{ll y,x,xx,flag;}b[N];
inline bool cmp1(node1 x,node1 y){return ((x.x==y.x)?(x.flag>y.flag):(x.x<y.x));}
inline bool cmp2(node2 x,node2 y){return ((x.y==y.y)?(x.flag>y.flag):(x.y<y.y));}
ll n,m,cnt,ans,f1[N],f2[N];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int inputx,inputy,inputxx,inputyy;
        cin>>inputx>>inputy>>inputxx>>inputyy;
        cnt++;
        a[cnt].x=inputx;a[cnt].y=inputy;a[cnt].yy=inputyy;a[cnt].flag=1;
        b[cnt].y=inputy;b[cnt].x=inputx;b[cnt].xx=inputxx;b[cnt].flag=1;
        cnt++;
        a[cnt].x=inputxx;a[cnt].y=inputy;a[cnt].yy=inputyy;
        b[cnt].y=inputyy;b[cnt].x=inputx;b[cnt].xx=inputxx;
    }
    sort(a+1,a+cnt+1,cmp1);
    sort(b+1,b+cnt+1,cmp2);
    for(int i=1;i<=cnt;i++)
    {
        if(a[i].flag)
        {
            for(int j=a[i].y;j<a[i].yy;j++)
                if(f1[j+M]++==0)
                    ans++;
        }
        else
        {
            for(int j=a[i].y;j<a[i].yy;j++)
                if((--f1[j+M])==0)
                    ans++;
        }

        if(b[i].flag)
        {
            for(int j=b[i].x;j<b[i].xx;j++)
                if(f2[j+M]++==0)
                    ans++;
        }
        else
        {
            for(int j=b[i].x;j<b[i].xx;j++)
                if((--f2[j+M])==0)
                    ans++;
        }
    }
    cout<<ans;
    return 0;
}
/*
notify-send “zyq要你经常回家看看” “喜报，阳历过了，跟你说一下，不用回来”
*/
