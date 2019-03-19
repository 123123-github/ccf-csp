#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 1008;

int n, m;
vector<int> G1[maxn], G2[maxn];

bool vis[maxn], same[maxn];

int bfs(vector<int> G[], int s)
{
	memset(vis, false, sizeof(vis));
	
	int cnt = 0;
	queue<int> Q;
	
	Q.push(s); vis[s] = true;
	if (!same[s]) { same[s] = true; cnt++; }
	
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		
		for (int i=0; i<G[u].size(); i++) {
			int v = G[u][i];
			if (vis[v]) continue;
			Q.push(v); vis[v] = true;
			if (!same[v]) { same[v] = true; cnt++; }
		}
	}
	
	return cnt;
}

int main()
{
	cin >> n >> m;
	for (int i=0, a, b; i<m; i++) {
		cin >> a >> b;
		G1[a].push_back(b);
		G2[b].push_back(a);
	}
	
	int cnt = 0;
	for (int v=1; v<=n; v++) {
		memset(same, false, sizeof(same));
		int send_num = bfs(G1, v);
		int take_num = bfs(G2, v);
		if (send_num + take_num == n) cnt++;
	}
	
	cout << cnt << '\n';
	
	return 0;
}
