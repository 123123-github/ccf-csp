#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1008;

int n, a[maxn];

int d[maxn][maxn], sum0[maxn];

inline int sum(int i, int j) { return sum0[j] - sum0[i-1]; }

int f(int i, int j)
{
	if (d[i][j] >= 0) return d[i][j];
	
	int t = 0x7fffffff;
	for (int k=i; k<=j-1; k++) {
		t = min ( t, f(i, k) + f(k+1, j) );
	}
	
	return d[i][j] = t + sum(i, j);
}

int main()
{
	cin >> n;
	for (int i=1; i<=n; i++) cin >> a[i];
	
	
	memset(d, -1, sizeof(d));
	for (int i=1; i<=n; i++) d[i][i] = 0;
	for (int i=1; i<=n; i++) sum0[i] = sum0[i-1] + a[i];
	cout << f(1, n) << '\n';
	
	return 0;
}

// time: 2.5 ~ 2.6s ...
