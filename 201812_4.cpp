#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 5 * 1e5 + 8, maxm = 1e5 + 8;

struct Edge {
	int u, v, d;
	bool operator<(const Edge& rhs) { return d < rhs.d; }
};

int n, m, root;

int p[maxn];
int find(int x) { return p[x]==x? x: p[x]=find(p[x]); }

bool Kruskal(int limit)
{
	for (int i=1; i<=n; i++) p[i] = i;
	
	int cnt = n;
	for (int i=0; i<m; i++) if (e[i].d <= limit) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) {
			p[x] = y; cnt--;
			if (cnt == 1) return true;
		}
	}
	
	return false;
}

int main()
{
	int maxw = 0, minw = 0x7fffffff;
	cin >> n >> m >> root;
	for (int u, v, t, i=0; i<m; i++) {
		cin >> u >> v >> t;
		e[i].u = u; e[i].v = v; e[i].d = t;
		maxw = max(maxw, t); minw = min(minw, t);
	}
	
	sort(e, e+m);
	
	// !!! binary search & Kruskal !!!
	while (minw <= maxw) {
		int midw = (minw + maxw) >> 1;
		
		if (Kruskal(midw)) maxw = midw - 1;
		else minw = midw + 1;
	}
	
	cout << minw;
	
	return 0;
}

/*
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 5 * 1e5 + 8, maxm = 1e5 + 8;

struct Edge {
	int u, v, d;
	bool operator<(const Edge& rhs) { return d < rhs.d; }
} e[maxm];

int n, m, root;

int p[maxn];
int find(int x) { return p[x]==x? x: p[x]=find(p[x]); }

int Kruskal()
{
	int ans = 0;
	for (int i=1; i<=n; i++) p[i] = i;
	
	int cnt = n;
	for (int i=0; i<m; i++) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) {
			p[x] = y; cnt--;
			ans = e[i].d;
			if (cnt == 1) return ans;
		}
	}
}

int main()
{
	int maxw = 0, minw = 0x7fffffff;
	cin >> n >> m >> root;
	for (int u, v, t, i=0; i<m; i++) {
		cin >> u >> v >> t;
		e[i].u = u; e[i].v = v; e[i].d = t;
		maxw = max(maxw, t); minw = min(minw, t);
	}
	
	sort(e, e+m);
		
	cout << Kruskal();
	
	return 0;
}
*/
