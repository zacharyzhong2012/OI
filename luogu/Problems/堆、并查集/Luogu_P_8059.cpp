#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define P pair<ll, ll>
#define se second
#define fi first
using namespace std;
const ll N = 4e5 + 9;
ll n, m, ban[N][3], ls[N], rs[N], id[N], dir[N], ans[N], vis[N];
vector<P> e[N];
inline void dfs(ll x, ll an)
{
    if (x == -1 || vis[x])
        return;
    vis[x] = 1;
    ans[x] = an;
    if (!ban[x][0])
        dfs(ls[x], an);
    if (!ban[x][1])
        dfs(rs[x], an);
    for (auto i : e[x])
        if (!ban[i.fi][i.se])
            dfs(i.fi, an);
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> ls[i] >> rs[i];
        if (ls[i] != -1)
            e[ls[i]].pb({i, 0});
        if (rs[i] != -1)
            e[rs[i]].pb({i, 1});
    }
    for (int i = 0; i < m; i++)
        cin >> id[i] >> dir[i], dir[i]--,
            ban[id[i]][dir[i]] = 1;
    dfs(1, -1);
    for (int i = m - 1; ~i; i--)
    {
        ban[id[i]][dir[i]] = 0;
        if (vis[id[i]])
            dfs(dir[i] ? rs[id[i]] : ls[id[i]], i);
        if (vis[dir[i] ? rs[id[i]] : ls[id[i]]])
            dfs(id[i], i);
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}