#include<bits/stdc++.h>
using namespace std;
const int N=5e3+9;
double dis[N],g[N][N];
int vis[N],n,m,a[N],b[N];
inline double getdis(double x,double y,double xx,double yy){
    return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}
inline double Prim(){
    double sum=0;
    for(int i=1;i<=n;i++)
        dis[i]=2147483647.00;
    for(int i=1;i<=n;i++){
        int tmp=-1;
        for(int j=1;j<=n;j++)
            if(!vis[j] && (tmp==-1 || dis[tmp]>dis[j]))
                tmp=j;
        if(i>1) sum+=dis[tmp];
        vis[tmp]=1;
        for(int j=1;j<=n;j++)
            dis[j]=min(dis[j],g[tmp][j]);
    }
    return sum;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            g[i][j]=getdis(a[i],b[i],a[j],b[j]);
        }
    printf("%.2lf",Prim());
    return 0;
}