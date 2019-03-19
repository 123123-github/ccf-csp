// priority_queue !!! OPERATOR< !!!
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 8, INF = 0x3f3f3f3f;

struct Edge {
	int from, to, dist;
};


struct HeapNode {
	int d, u;
	bool operator<(const HeapNode& rhs) const {
		return d > rhs.d;
	}
};

struct Dijkstra {
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool done[maxn];
	int d[maxn];
	
	void init(int n)
	{
		this->n = n;
		this->m = 0;
		for (int i=1; i<=n; i++) G[i].clear();
		edges.clear();
	}
	
	void addEdge(int from, int to, int dist) {
		edges.push_back((Edge){from, to, dist});
		G[from].push_back(m++);
	}
	
	void dijkstra(int s) {
		priority_queue<HeapNode> Q;
		
		for (int i=1; i<=n; i++) d[i] = INF;
		d[s] = 0;
		memset(done, false, sizeof(done));
		
		Q.push((HeapNode){0, s});
		while (!Q.empty()) {
			HeapNode x = Q.top(); Q.pop();
			int u = x.u;
			
			if (done[u]) continue;
			done[u] = true;
			
			for (int i=0; i<G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				
				if ( d[e.to] > max(d[u], e.dist)) {
					d[e.to] = max(d[u], e.dist);
					Q.push((HeapNode){d[e.to], e.to});
				}
			}
		}
	}
} D;

int main()
{
	int n, m;
	cin >> n >> m;
	
	D.init(n);
	for (int i=0, a, b, dist; i<m; i++) {
		cin >> a >> b >> dist;
		D.addEdge(a, b, dist);
		D.addEdge(b, a, dist);
	}
	
	D.dijkstra(1);
	
	cout << D.d[n] << '\n';
	
	return 0;
}
