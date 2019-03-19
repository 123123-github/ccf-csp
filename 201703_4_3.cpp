// Kruskal
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 100000 + 5, maxm = 200000 + 5;

int n, m;

int p[maxn];
int find(int x) { return p[x]==x? x: p[x]=find(p[x]); }

struct Edge
{
	int from, to, dist;
	bool operator<(const Edge& rhs) const {
		return dist < rhs.dist;
	}
} edges[maxm];

int Kruskal()
{
	for (int i=1; i<=n; i++) p[i] = i;
	sort(edges, edges+m);
	
	int cnt = n;
	for (int i=0; i<m; i++) {
		Edge& e = edges[i];
		int x = find(e.from);
		int y = find(e.to);
		if (x != y) {
			p[x] = y; cnt--;
			if (find(1) == find(n)) return e.dist;
		}
	}
	
	return -1;
}

int main()
{
	cin >> n >> m;
	for (int i=0, a, b, c; i<m; i++) {
		cin >> a >> b >> c;
		edges[i] = (Edge){a, b, c};
	}
	
	cout << Kruskal() << '\n';
	
	return 0;
}
