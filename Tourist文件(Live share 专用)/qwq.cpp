#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=5e5+7;
int n,a[N],lastans=0;
pair<int,int> ST[N][26];
stack<pair<int,int> > z;
void init()
{
    for(int i=n;i>=1;i--){
        while(!z.empty()&&z.top().x<=a[i]) z.pop();
        if(z.empty()) ST[i][0].x=n+1;
        else ST[i][0].x=z.top().y;
        
        z.push({i,a[i]});
    }//A了
    for(int i=1;i<=n;i++) cout<<ST[i][0].x<<" "<<ST[i][0].y<<endl;
}
signed main()
{
    int t;
    cin>>n>>t;
    for(int i=1;i<=n;i++) cin>>a[i];
    init();
    while(t--){
        int u,v,l,q;
        cin>>u>>v;
        l=1+(u^lastans)%n;
        q=1+(v^(lastans+1))%(n-l+1);

    }
    return 0;
}
//6,还是一起学习吧
//我要泄(写)题 别吵 我是CCf
//看看我