#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+9;
ll n,T;
inline string getnum(int x){
    if(x==1) return "1";
    else if(x==2) return "(1+1)";
    else if(x==3) return "(1+1+1)";
    else{
        int tmp=sqrt(x),tp=x-tmp*tmp;
        if(tp!=0)return getnum(tmp)+"*"+getnum(tmp)+"+"+getnum(tp);
        else return getnum(tmp)+"*"+getnum(tmp);
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