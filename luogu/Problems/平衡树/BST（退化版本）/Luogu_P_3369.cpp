#include<bits/stdc++.h>
#define fi first 
#define se second
#define Inf (ll)1e9
#define ll long long
#define P pair<ll,ll>
using namespace std;
const ll N=1e5+9;
ll cnt,q,root;
struct Bst{
    struct node{
        ll lson,rson;
        ll siz,val,numv;
    }d[N<<1];
    inline ll Newnode(ll x){
        d[++cnt]={-1,-1,1,x,1};
        return cnt;
    }
    inline void Build(){
        Newnode(-Inf);
        Newnode(Inf);
        d[1].rson=2;
        root=1;
    }
    inline void Insert(ll val){//opt:1
        ll pos=root;
        while(pos){
            if(val>d[pos].val){
                if(d[pos].rson!=-1){
                    pos=d[pos].rson;
                    continue;
                }
                break;
            }else if(val==d[pos].val){
                break;
            }else{
                if(d[pos].lson!=-1){
                    pos=d[pos].lson;
                    continue;
                }
                break;
            }
        }
        if(val==d[pos].val) d[pos].numv++;
        else if(val<d[pos].val) d[pos].lson=Newnode(val);
        else d[pos].rson=Newnode(val);
    }
    inline P gm_num(ll val){//opt:5
        ll pos=root,ans=INT_MIN;
        while(pos){
            if(val==d[pos].val){
                if(d[pos].rson!=-1){
                    pos=d[pos].rson;
                    while((d[pos].lson+1))
                        pos=d[pos].lson;
                    ans=d[pos].val;
                }
                break;
            }
            if(val>d[pos].val){
                ans=max(ans,d[pos].val);
                if(d[pos].rson!=-1){
                    pos=d[pos].rson;
                    continue;
                }
                break;
            }else{
                if(d[pos].lson!=-1){
                    pos=d[pos].lson;
                }
                continue;
            }
        }
        return {ans,pos};
    }
    inline P gx_num(ll val){//opt:6
        ll pos=root,ans=INT_MAX;
        while(pos){
            if(val==d[pos].val){
                if(d[pos].lson!=-1){
                    pos=d[pos].lson;
                    while((d[pos].rson+1))
                        pos=d[pos].rson;
                    ans=d[pos].val;
                }
                break;
            }
            else if(val>d[pos].val){
                if(d[pos].lson!=-1){
                    pos=d[pos].lson;
                    continue;
                }
                break;
            }else{
                ans=min(ans,d[pos].val);
                if(d[pos].rson!=-1){
                    pos=d[pos].rson;
                }
                continue;
            }
        }
        return {ans,pos};
    }
    inline void Output(){
        for(int i=1;i<=cnt;i++)
            cout<<d[i].lson<<' '<<d[i].rson<<' '<<d[i].val<<endl;
        cout<<endl;
    }
}BST;
int main(){
    BST.Build();
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        ll opt,x;
        cin>>opt>>x;
        if(opt==1)BST.Insert(x);
        else if(opt==5)cout<<BST.gm_num(x).fi<<endl;
        else if(opt==6)cout<<BST.gx_num(x).fi<<endl;
        BST.Output();
    }
    return 0;
}
/*
BST:
any x is no smaller than its leftson' kids
any x is no bigger than its rightson' kids

1. insert:
*/