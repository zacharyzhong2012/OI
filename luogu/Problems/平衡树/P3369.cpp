#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e6+9;
struct node
{
	ll lson,rson;
	ll val,rnd;
	ll sz;
}tr[N];
ll cnt,root;
inline void push_up(ll x) {tr[x].sz=tr[tr[x].lson].sz+tr[tr[x].rson].sz+1;}
inline void make_new(ll x)
{
	tr[++cnt].sz=1;
	tr[cnt].lson=tr[cnt].rson=0ll;
	tr[cnt].val=x;tr[cnt].rnd=rand();
}
inline void split(ll u,ll x,ll &l,ll &r)
{
	if(u==0) return l=r=0,void();
	if(tr[u].val<=x) l=u,split(tr[u].rson,x,tr[u].rson,r);
	else r=u,split(tr[u].lson,x,l,tr[u].lson);
	push_up(u);
}
inline ll merge(ll l,ll r)
{
	if(l==0 || r==0) return l+r;
	if(tr[l].rnd>tr[r].rnd) return tr[l].rson=merge(tr[l].rson,r),push_up(l),l;
	else return tr[r].lson=merge(l,tr[r].lson),push_up(r),r;
}
inline void insert(ll x)
{
	ll l,r;split(root,x,l,r);make_new(x);
	root=merge(merge(l,cnt),r);
}
inline void del(ll x)
{
	ll l,r,p=0;split(root,x,l,r);split(l,x-1,l,p);
	root=merge(merge(l,merge(tr[p].lson,tr[p].rson)),r);
}
inline void rnk(ll x)
{
	ll l,r;
	split(root,x-1,l,r);
	cout<<tr[l].sz+1<<endl;
	root=merge(l,r);
}
inline ll Find(ll x,ll f)
{
	if(f==tr[tr[x].lson].sz+1) return x;
	if(f<=tr[tr[x].lson].sz) return Find(tr[x].lson,f);
	return Find(tr[x].rson,f-tr[tr[x].lson].sz-1);
}
inline void get_lson(ll x)
{
	ll l,r;
	split(root,x-1,l,r);
	cout<<tr[Find(l,tr[l].sz)].val<<endl;
	root=merge(l,r);
}
inline void get_rson(ll x)
{
	ll l,r;
	split(root,x,l,r);
	cout<<tr[Find(r,1)].val<<endl;
	root=merge(l,r);
}
int main()
{
	srand(time(0));
	ll n;
	cin>>n;
	while(n--)
	{
		ll opt,x;
		cin>>opt>>x;
		if(opt==1) insert(x);
		if(opt==2) del(x);
		if(opt==3) rnk(x);
		if(opt==4) cout<<tr[Find(root,x)].val<<endl;
		if(opt==5) get_lson(x);
		if(opt==6) get_rson(x);
	}
	return 0;
}
