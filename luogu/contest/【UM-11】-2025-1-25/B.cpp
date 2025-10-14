#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+9;
ll n,T;
inline string calc(int x){
    string ans="";
    for(int i=1;i<(ll)log2(x);i++)
        ans=ans+"(1+1)*";
    return ans+"(1+1)";
}
inline string getnum(int x){
    if(x==1) return "1";
    else if(x==2) return "(1+1)";
    else if(x==3) return "(1+1+1)";
    else{
        int tmp=(1ll<<((ll)log2(x)));
        int tp=(x-tmp);
        string ans=calc(tmp);
        if(tp)return ans+"+"+getnum(tp);
        else return ans;
    }
}
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        cout<<getnum(n)<<endl;
    }
    return 0;
}