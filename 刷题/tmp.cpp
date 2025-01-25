#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int n,m,dis[N][N],fa[N];
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void merge(int x,int y){
    fa[Find(x)]=Find(y);
}
int main(){
    cin>>n;
    cin>>m;
    int x,y;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        char opt;
        cin>>opt;
        if(opt=='F'){
            cin>>x>>y;
            merge(x,y);
        }else{
            cin>>x>>y;
            dis[x][y]=1;
            dis[y][x]=1;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(dis[i][j])
                for(int k=1;k<=n;k++)
                    if(dis[j][k]){
                        merge(i,k);
                    }
    int sum=0;
    for(int i=1;i<=n;i++)
        if(fa[i]==i)
            sum++;
    cout<<sum;
    return 0;
}