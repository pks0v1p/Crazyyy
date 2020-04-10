#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair < int, int >
#define pi3 pair < int, pii >
#define fi  first
#define se  second
int n, k, f[2003], a[2003][2003], d[2003][2003], sum, par[2003];
bool edge[2003][2003];
priority_queue < pi3, vector < pi3 >, greater < pi3 > > q;
void    in()
{
    cin >> n >> k;
    sum = 0;
    while (!q.empty())
        q.pop();
    for (int i = 1; i <= n; i++)
        cin >> f[i], sum += f[i], par[i] = -1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            if (i != j) edge[i][j] = 1;
            else    edge[i][j] = 0;
            d[i][j] = a[i][j] - max (f[i], f[j]);
            int u = i, v = j;
            if (f[u] > f[v])    swap (u, v);
            if (i < j)  q.push({d[i][j], {u, v}});
        }
}
int     root (int u)
{
    if (par[u] < 0) return u;
    par[u] = root(par[u]);
    return  par[u];
}
void    xuly()
{
    int cnt = 0;
    while (q.size())
    {
        //cout << cnt << '\n';
        if (cnt >= n - k && q.top().fi > 0) break;
        int u = q.top().se.fi, v = q.top().se.se, x = q.top().fi;
        q.pop();
        if (root(u) != u || root(v) != v)   continue;
        sum += x;
        cnt++;
        par[v] = u;
        for (int i = 1; i <= n; i++)
        {
            if (!edge[v][i])    continue;
            edge[v][i] = 0, edge[i][v] = 0;
            if (d[u][i] > a[v][i] - max (f[u], f[i]))
            {
                a[u][i] = a[v][i];
                a[i][u] = a[u][i];
                d[u][i] = a[v][i] - max (f[u], f[i]);
                d[i][u] = d[u][i];
                int xx = u, yy = i;
                if (f[u] > f[i])    swap (xx, yy);
                q.push({d[u][i], {xx, yy}});
            }
        }
    }
    cout << sum << '\n';
}
main ()
{
    freopen("trash.inp","r",stdin);
    freopen("trash.out","w",stdout);
    int T;
    cin >> T;
    while (T--)
    {
        in();
        xuly();
    }
}
