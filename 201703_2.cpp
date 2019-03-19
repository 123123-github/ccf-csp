#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1005;

int n, m;
int pre[maxn], next[maxn], node[maxn];

const int head = 0;

void link(int x, int y)
{
	next[x] = y;
	pre[y] = x;
}

void add_node(int x, int p, int y)
{
	next[x] = pre[y] = p;
	pre[p] = x, next[p] = y;
}

void creat_list()
{
	memset(pre, -1, sizeof(pre));
	memset(next, -1, sizeof(next));
	
	pre[head] = n; next[n] = head;
	for (int i=0; i<n; i++) next[i] = i + 1;
	for (int i=1; i<=n; i++) pre[i] = i - 1;
	for (int i=0; i<=n; i++) node[i] = i;
}

int main()
{
	cin >> n >> m;
		
	creat_list();
	
	int p, q;
	int a, dx;
	int x, y, xx, yy;
	while (m--)
	{
		cin >> p >> dx;
		
		q = p;
		x = pre[p], y = next[p];
		
		if (dx>0) {
			while (dx--) q = next[q];
			xx = q, yy = next[q];
		} else {
			while (dx++) q = pre[q];
			xx = pre[q], yy = q;
		}
		
		link(x, y);
		add_node(xx, p, yy);
	}
	
	for (int i=next[head]; i!=head; i=next[i]) {
		cout << node[i] << ' ';
	}
	
	return 0;
}
