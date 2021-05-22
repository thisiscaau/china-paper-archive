/*
thisiscaau's code
trying my best for a better future
*/


#include <bits/stdc++.h>

#define fileopen(a, b) freopen(((std::string)a + ".inp").c_str(), "r", stdin); freopen(((std::string)b + ".out").c_str(), "w", stdout);
#define fileopen1(a) freopen(((std::string)a + ".inp").c_str(), "r", stdin); freopen(((std::string)a + ".out").c_str(), "w", stdout);

using namespace std;
#define ll long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
ll const mod = 1e9 + 7, MAXN = 2e5 + 5,oo = 3e18;

ll n,m,q;

struct ask {
	ll u,v,type;
} que[MAXN];

struct edge {
	ll u,v,w;
	edge () {}
	edge (ll a,ll b,ll c) : u(a),v(b),w(c) {}
	bool operator < (const edge &other) const{
		return w < other.w;
	}
};

vector<edge> g,rev;

ll w[1001][1001];
bool del[1001][1001];
ll par[1001],fa[1001],mark[1001],rec[1001];
vector<ll> ans;


// Functions

ll find (ll u){
	return (par[u] == u) ? u : find(par[u]);
}

bool same_set(ll u,ll v){
	return find(u) == find(v);
}

void reroot (ll u){
	// reverse chain
	vector<ll> chain;
	ll node = u;
	while (node){
		chain.pb(node);
		node = fa[node];
	}
	for (int i = 1 ; i < chain.size() ; i++){
		fa[chain[i]] = chain[i - 1];
	}
}

void reroot2 (vector<ll> chain){
	for (int i = 1 ; i < chain.size() ; i++){
		fa[chain[i]] = chain[i - 1];
	}
}


signed main() {
#ifdef thisiscaau
	fileopen("input", "output");
#endif
#ifndef thisiscaau
	// fileopen1("LAH");
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m >> q;
	for (int i = 1 ; i <= m ; i++){
		ll u,v,ww; cin >> u >> v >> ww;
		g.push_back(edge(u,v,ww));
		w[u][v] = w[v][u] = ww;
	}
	for (int i = 1 ; i <= q ; i++){
		cin >> que[i].type >> que[i].u >> que[i].v;
		if (que[i].type == 2){
			del[que[i].u][que[i].v] = true;
			del[que[i].v][que[i].u] = true;
		}
	}
	for (auto e : g){
		ll u = e.u,v = e.v;
		if (!del[u][v]){
			rev.pb(e);
		}
	}

	sort(rev.begin(),rev.end());

	for (int i = 1 ; i <= n ; i++){
		par[i] = i;
		fa[i] = 0;
	}

	for (auto e : rev){
		ll u = e.u,v = e.v;
		if (same_set(u,v)) continue;
		ll uu = find(u),vv = find(v);
		par[uu] = vv;
		reroot(u);
		fa[u] = v;
	}
	
	for (int i = q ; i >= 1 ; i--){
		ll u = que[i].u,v = que[i].v,t = que[i].type;
		ll node = u; rec[node] = 0;
		while (node){
			mark[node] = i;
			rec[fa[node]] = max(rec[node],w[node][fa[node]]);
			node = fa[node];
		}

		ll node2 = v,mx = 0;
		while (node2 && mark[node2] != i){
			mx = max(mx,w[node2][fa[node2]]);
			node2 = fa[node2];
		}

		ll max_weight = max(rec[node2],mx);
		if (t == 1){
			ans.pb(max_weight);
		}
		else {
			if (max_weight <= w[u][v]) continue;
			// wlog supposing dist[u] > dist[v]
			if (mx > rec[node2]) swap(u,v);
			vector<ll> chain;
			ll node = u;
			while (1){
				if (!node) break;
				chain.pb(node);
				if (w[node][fa[node]] == max_weight) break;
				node = fa[node];
			}
			reroot2(chain);
			fa[u] = v;
		}
	}
	reverse(ans.begin(),ans.end());
	for (ll i : ans){
		cout << i << endl;
	}
}