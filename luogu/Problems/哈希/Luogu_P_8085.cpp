#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+9,Base=131,Mod=1e13+7;
ll lena,lenb,prea[N],preb[N],nxt[N];
string a[N],b[N];
inline void Getpre(string src[],ll pre[],ll num){
    unordered_map<string,int>lastpos;
    for(int i=1;i<=num;i++)
        pre[i]=lastpos[src[i]],
        lastpos[src[i]]=i;
}
inline void Getnxt(){
    int i=2,j=1;
    while(i<=lenb){
        if(i-preb[i]==j-preb[j] || !preb[j] && preb[i]<=i-j)
            nxt[i++]=j++;
        else if(j>1) j=nxt[j-1]+1;
        else i++;
    }
}
inline void KMP(){
    int i=1,j=1;
    while(i<=lena){
        if(i-prea[i]==j-preb[j] || !preb[j] && prea[i]<=i-j)i++,j++;
        else if(j>1) j=nxt[j-1]+1;
        else i++;
        if(j>lenb){cout<<i-lenb;exit(0);};
    }
}
int main(){
    string input;
    while(cin>>input && input!="$")a[++lena]=input;
    while(cin>>input && input!="$")b[++lenb]=input;
    Getpre(a,prea,lena);Getpre(b,preb,lenb);
    Getnxt();KMP();cout<<-1;
    return 0;
}