/*                 thisiscaau's  code              
        What’s happened happened. Which is an expression of faith 
    in the mechanics of the world. It’s not an excuse to do nothing.
*/
/* shortcuts */
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
/* constants */
ll const inf = 1e9 + 7, MAXN = 1e6 + 5;
/* declaration */
ll n,m,q,idx;
struct edge{
    int u,v,w;  
} e[MAXN],e1[MAXN];
struct query{
    int k,u,v;
} task[MAXN];
ll g[1001][1001];
ll par[1001],fa[1001],rec[1001],sign[1001];
ll res[MAXN];
/* workspace */
bool comp(edge a,edge b){
    return a.w < b.w;
}
ll find(ll u){
    return par[u] == u ? u : find(par[u]);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1 ; i <= m ; i++){
        cin >> e1[i].u >> e1[i].v >> e1[i].w;
    }
    for (int i = 1 ; i <= q ; i++){
        cin >> task[i].k >> task[i].u >> task[i].v;
        if (task[i].k == 2) g[task[i].u][task[i].v] = 1,g[task[i].v][task[i].u] = 1;
    }
    for (int i = 1;i <= m ; i++) {
        ll &cur = g[e1[i].u][e1[i].v];
        if (!cur) e[++idx] = e1[i];
        cur = g[e1[i].v][e1[i].u] = e1[i].w; // g array stores edge weight
    }
    sort(e+1,e+1+idx,comp);
    // initialize disjoint set union
    for (int i = 1 ; i <= n ; i++) par[i] = i;
    // kruskal
    for (int i = 1 ; i <= idx ; i++){
        ll u = e[i].u , v = e[i].v;
        ll fu = find(u), fv = find(v);
        if (fu == fv) continue;
        par[fu] = fv;
        // rotate sequence
        ll ff = fa[u], qq = u;
        while (ff){
            swap(fa[ff],qq);
            swap(ff,qq);
        }
        fa[u] = v;
    }
    // solving queries backwardly
    ll cnt = 0;
    for (int i = q ; i >= 1 ; i--){
        ll u = task[i].u , v = task[i].v, cur = u;
        rec[cur] = 0;
        while (cur){
            sign[cur] = i; // marking query index
            rec[fa[cur]] = max(rec[cur],g[cur][fa[cur]]);
            cur = fa[cur];
        }
        // finding lca of u and v along with "max" weight
        ll lca = v,mx = 0; // it must be v or some ancestor of v
        while (lca && sign[lca] != i){ // going up until meet
            mx = max(mx,g[lca][fa[lca]]);
            lca = fa[lca]; // going up
        }
        ll ans = max(mx,rec[lca]);
        if (task[i].k == 1){
            res[++cnt] = ans;
        }
        else {
            if (ans <= g[u][v]) continue;
            if (ans > rec[lca]) swap(u,v);
            // joining
            ll ff = fa[u], qq = u;
            while (ff){
                swap(fa[ff],qq);
                swap(ff,qq);
            }
            fa[u] = v;
        }
    }
    for (int i = cnt ; i >= 1 ; i--) cout << res[i] << endl;
}