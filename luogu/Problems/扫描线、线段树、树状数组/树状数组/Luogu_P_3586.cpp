#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) (x&(-x))
using namespace std;
const ll N=2e6+9;
ll tr1[N],tr2[N];
ll cnt,n,m,opt[N],ct;
ll ch[N][2],num[N],sum,a[N];
unordered_map<ll,ll>mp;
inline void change1(int x,int y){
    for(;x<=ct;x+=lowbit(x))
        tr1[x]+=y;
}
inline ll query1(int x){
    ll sum=0;
    for(;x;x-=lowbit(x))
        sum+=tr1[x];
    return sum;
}
inline void change2(int x,int y){
    for(;x<=ct;x+=lowbit(x))
        tr2[x]+=y;
}
inline ll query2(int x){
    ll sum=0;
    for(;x;x-=lowbit(x))
        sum+=tr2[x];
    return sum;
}
int main(){
    cin>>n>>m;num[++cnt]=0;
    for(int i=1;i<=m;i++){
        char s;
        cin>>s>>ch[i][0]>>ch[i][1];
        if(s=='U'){
            opt[i]=1;
            num[++cnt]=ch[i][1];
        }
        else{
            opt[i]=2;
            num[++cnt]=ch[i][1];
        }
    }
    sort(num+1,num+cnt+1);
    for(int i=1;i<=cnt;i++) 
        if(!mp[num[i]])
            mp[num[i]]=++ct;
    for(int i=1;i<=n;i++)
        change1(ct-1,1);
    for(int i=1;i<=m;i++){
        if(opt[i]==1){
            change1(ct-mp[a[i]]);
        }
    }
    return 0;
}