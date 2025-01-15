#include<bits/stdc++.h>
#define ll long long
#define P pair<ll,ll>
#define fi first
#define se second
using namespace std;
const ll N=8e5+9;
struct node{ll x,h,flag;}a[N];
inline bool cmp(node x,node y){
    if(x.x!=y.x) return x.x<y.x;
    if(x.flag!=y.flag) return x.flag<y.flag;
    if(x.flag==1) return x.h>y.h;
    else return x.h<y.h;
}
ll n,cnt,num;
multiset<ll>Myset;
P ans[N];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        ll h,l,r;
        cin>>h>>l>>r;
        a[++cnt].x=l;a[cnt].h=h;a[cnt].flag=1;
        a[++cnt].x=r;a[cnt].h=h;a[cnt].flag=2;
    }
    sort(a+1,a+cnt+1,cmp);
    Myset.insert(0);
    for(int i=1;i<=cnt;i++)
    {
        ll maxx=*(Myset.rbegin());
        if(a[i].flag==1)
        {
            if(a[i].h<=maxx) Myset.insert(a[i].h);
            else
            {
                ans[++num]={a[i].x,maxx};
                ans[++num]={a[i].x,a[i].h};
                Myset.insert(a[i].h);
            }
        }else
        {
            if(a[i].h==maxx && Myset.count(maxx)==1)
            {
                Myset.erase(maxx);
                ans[++num]={a[i].x,a[i].h};
                ans[++num]={a[i].x,*(Myset.rbegin())};
            }else Myset.erase(Myset.find(a[i].h));
        }
    }
    cout<<num<<endl;
    for(int i=1;i<=num;i++)
        cout<<ans[i].fi<<' '<<ans[i].se<<endl;
    return 0;
}
/*
我的思路就是，对于每一个房子的左右两边那一条垂直于x轴的线段
你都把他按照x排个序，然后你从左往右边扫，现在所有包含这个点的房子都存在了Myset里面
然后你就看，如果这个点他是左端点，那么我们就往Myset里面加，这种情况下还要判断他的最大值和目前的最大值
因为如果现在这个点的高度比已知的最大值还要高，那么这个房子就会凸出来，那么我们就要统计答案
否则我们就把这个房子加入到Myset里面，将会用到
然后我们对于这个是右端点的边进行统计
如果这个右端点高度是最高的，那么我们还要判断是不是只有他一个最高的了，因为如果有多个最高，这个房子就不会凸出来
同理，如果他不是最高的或者有多个最高，那我们就不用统计答案，反之这个地方会凹进去
然后就做完了。。。
*/