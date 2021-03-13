/*                 thisiscaau's  code              
        What’s happened happened. Which is an expression of faith 
    in the mechanics of the world. It’s not an excuse to do nothing.
*/
/* shortcuts */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
/* constants */
ll const inf = 1e9 + 7, MAXN = 30000 + 5;
/* declaration */
ll n,timer = 0;
vector<ll> g[MAXN];
ll ett[2*MAXN];
ll st[MAXN];
ll lg[2*MAXN];
ll dp[2*MAXN][18];
ll depth[MAXN];
/* workspace */
void dfs(ll node,ll par){
    depth[node] = depth[par] + 1;
    ett[++timer] = depth[node];
    st[node] = timer;
    for (auto dest : g[node]){
        if (dest != par){
            dfs(dest,node);
            ett[++timer] = depth[node];
        }
    }
}
void rmq(){
    lg[0] = -1;
    for (int i = 1 ; i <= timer ; i++){
        dp[i][0] = ett[i];
        lg[i] = lg[i/2] + 1;
    }
    for (int j = 1 ; j <= 17 ; j++){
        for (int i = 1 ; i + (1 << j) - 1 <= timer ; i++){
            dp[i][j] = min(dp[i][j-1],dp[i+(1 << (j-1))][j-1]);
        }
    }
}
ll dist(ll u,ll v){
    ll l = min(st[u],st[v]), r = max(st[u],st[v]);
    ll j = lg[r-l+1];
    ll common = min(dp[l][j],dp[r-(1<<j)+1][j]);
    return depth[u] + depth[v] - 2*common;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1 ; i < n ; i++){
        ll u,v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,0);
    rmq();
    ll q,pos,res = 0;
    cin >> q >> pos;
    for (int i = 1 ; i < q ; i++){
        ll dest; cin >> dest;
        res += dist(pos,dest);
        pos = dest;
    }
    cout << res << endl;
}