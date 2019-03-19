#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 10000 + 8;

struct Edge
{
	int from, to, dist;
};

struct HeapNode
{
	int d, u, pre;
	bool operator<(const HeapNode& rhs) const {
		return d == rhs.d? pre > rhs.pre: d > rhs.d;;
	}
};

struct Dijkstra
{
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool done[maxn];
	int d[maxn];
	int sum;
	
	void init(int n)
	{
		this->n = n;
		this->m = 0;
		for (int i=1; i<=n; i++) G[i].clear();
		edges.clear();
	}
	
	void AddEdge(int from, int to, int dist)
	{
		edges.push_back( (Edge){from, to, dist} );
		G[from].push_back(m++);
	}
	
	void dijkstra(int s)
	{
		priority_queue<HeapNode> Q;
		
		memset(d, 0x3f, sizeof(d));
		memset(done, false, sizeof(done));
		sum = 0;
		
		d[s] = 0;
		Q.push( (HeapNode){0, s, 0} );
		while (!Q.empty())
		{
			HeapNode x = Q.top(); Q.pop();
			int u = x.u;
			
			if (done[u]) continue;
			done[u] = true;
			sum += x.pre;
			
			for (int i=0; i<G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				
				if (d[e.to] >= d[u] + e.dist) {
					d[e.to] = d[u] + e.dist;
					Q.push( (HeapNode){d[e.to], e.to, e.dist} );
				}
			}
		}
	}
	
} D;

int main()
{
	int n, m; cin >> n >> m;
	D.init(n);
	for (int i=0, a, b, c; i<m; i++) {
		cin >> a >> b >> c;
		D.AddEdge(a, b, c);
		D.AddEdge(b, a, c);
	}
	
	D.dijkstra(1);
	
	cout << D.sum << '\n';
	
	return 0;
}
