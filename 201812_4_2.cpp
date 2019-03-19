#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 5 * 1e5 + 5, maxm = 1e5 + 5;

int n, m, root;

struct Edge
{
	int from, to, dist;
	bool operator<(const Edge& rhs) const {
		return dist < rhs.dist;
	}
} e[maxm];

int p[maxn];
int find(int x) { return x==p[x]? x: p[x]=find(p[x]); }

int main()
{
	cin >> n >> m >> root;
	for (int i=0, a, b, t; i<m; i++) {
		cin >> a >> b >> t;
		e[i] = (Edge){a, b, t};
	}
	
	sort(e, e+m);
	for (int i=1; i<=n; i++) p[i] = i;
	
	int cnt = n;
	for (int i=0; i<m; i++)	 {
		Edge& e0 = e[i];
		int x = find(e0.from), y = find(e0.to);
		if (x != y) {
			p[x] = y;
			cnt--;
			if (cnt == 1) {
				cout << e0.dist << '\n';
				break;
			}
		}
	}
	
	return 0;
}
