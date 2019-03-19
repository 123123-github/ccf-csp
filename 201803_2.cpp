#include <iostream> 
#include <cstring>
using namespace std;

const int maxn = 105, maxl = 1005;

int n, L, t;
int p[maxn], dx[maxn], vis[maxl];

int main()
{
	cin >> n >> L >> t;
	for (int i=1; i<=n; i++) cin >> p[i];
	for (int i=1; i<=n; i++) dx[i] = 1;
	
	while (t--)
	{
		memset(vis, 0, sizeof(vis));
		for (int i=1; i<=n; i++) {
			p[i] += dx[i];									// move
			
			if ( vis[p[i]] ) { dx[vis[p[i]]] = -dx[vis[p[i]]]; dx[i] = -dx[i]; }
			else vis[p[i]] = i;
			
			if (p[i] == 0 || p[i] == L) dx[i] = -dx[i];		// clash
		}
	}
	
	for (int i=1; i<=n; i++) cout << p[i] << ' ';
	
	return 0;
}
