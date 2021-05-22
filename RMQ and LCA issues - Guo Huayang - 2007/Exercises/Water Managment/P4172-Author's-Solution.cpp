#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) x.size())
#define show(x) cerr << #x << " is " << x << endl;
#define show2(x, y) cerr << #x << " is " << x << ", " << #y << " is " << y << endl;
typedef long long lint;
typedef pair<lint, lint> ii;

///Suppose there are no edges removed. We can answer each query online using a kruskal tree or a line tree in O(logN) time [O(1)] is possible but not needed
///Now we reverse the process, so we're adding edges instead
///When we add an edge, we recompute the new MST and hence construct the new kruskal tree
///each recompution, we only consider the N-1 of the previous MST and the new added edge, hence each reconstruction takes 5000*n time
struct query{ lint k, u, v, w; };
struct edge{ lint u, v, w; };
vector<query> queries;
map<ii, int> edges;
vector<int> ans;

vector<edge> mst;

int n, m, Q; 
struct kruskal{
	int p[2005];
	int weight[2005];
	int corr[2005];
	int cnt;
	int L[2005];
	int R[2005];
	
	int tree[2005];
		
	vector<int> weights;
	
	int findSet(int u){
		if(u == p[u]) return u;
		else return p[u] = findSet(p[u]);
	}
	
	void dfs(int u){
		//show(u);
		if(u <= n){
			corr[u] = sz(weights);
			return;
		}
		
		dfs(L[u]);
		weights.push_back(weight[u]);
		dfs(R[u]);
	}
	
	void create(vector<edge> edges){
		cnt = n+1; // seperating edges node from regular nodes
		weights.clear();
		for(int i = 0;i < 2*n+1;i++){
			p[i] = i; // initialize
			weight[i] = 0;
			L[i] = 0, R[i] = 0;
			tree[i] = 0;
		}
		sort(all(edges), [&](edge a, edge b){ return a.w < b.w; });
		
		vector<edge> newmst;
		
		for(edge e : edges){
			int u = findSet(e.u), v = findSet(e.v);
			if(u == v) continue;
			newmst.push_back(e);
			p[u] = cnt;
			p[v] = cnt;
			weight[cnt] = e.w;
			L[cnt] = u;
			R[cnt] = v;
			cnt++;
		}
		
		dfs(cnt-1);
		
		//for(int i = 1;i <= n;i++) show(corr[i]);
		//for(int x : weights) show(x);
		swap(mst, newmst);
		newmst.clear();
		
		for(int i = 0;i < sz(weights);i++) tree[i+n] = weights[i];
		for(int i = n-1;i > 0;i--) tree[i] = max(tree[i<<1], tree[i<<1|1]);
	}
	
	int query(int l, int r){
		r = corr[r], l = corr[l];
		if(l > r) swap(l, r);
		int res = 0;
		for(l += n, r += n;l < r;l >>= 1, r >>= 1){
			if(l&1) res = max(res, tree[l++]);
			if(r&1) res = max(res, tree[--r]);
		}
		return res;
	}
	
} KRT;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	cin >> n >> m >> Q;
	
	for(int i = 0;i < m;i++){
		int u, v, w; cin >> u >> v >> w;
		if(u > v) swap(u,v);
		edges[ii(u,v)] = w;
	}
	
	while(Q--){
		int k, u, v; cin >> k >> u >> v;
		if(u > v) swap(u,v);
		if(k == 1) queries.push_back({k,u,v,-1});
		else{
			auto it = edges.find(ii(u,v));
			queries.push_back({k,u,v,it->second});
			edges.erase(it);
		}
	}
	
	for(auto e : edges){
		mst.push_back({e.first.first, e.first.second, e.second});
	}
	
	KRT.create(mst);
	
	reverse(all(queries));
	for(query &q : queries){
		if(q.k == 1){
			q.w = KRT.query(q.u, q.v);
		}
		else{
			mst.push_back({q.u,q.v,q.w});
			KRT.create(mst);
		}
	}
	
	reverse(all(queries));
	for(query &q : queries){
		if(q.k == 1) cout << q.w << "\n";
	}
}