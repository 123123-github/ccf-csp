#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int maxn = 55;

int r, c;
char pic[maxn][maxn];


int acs_num, tot;
bool vis[maxn][maxn];
bool acs[maxn][maxn];

void get_start_pos(int& x, int& y) { for (int i=0; i<r; i++) for (int j=0; j<c; j++) if (pic[x=i][y=j] == 'S') return; }

bool dfs(int x, int y)
{
	if (x < 0 || x >= r || y < 0 || y >= c) return false;
	if (pic[x][y] == '#') return false;
	
	if (vis[x][y]) return acs[x][y];
	
	vis[x][y] = true;
	
	bool find = false;
	switch (pic[x][y]) {
		case 'T':
			acs_num = acs[x][y]? acs_num: acs_num + 1;
			acs[x][y] = true;
			dfs(x, y+1); dfs(x+1, y); dfs(x, y-1); dfs(x-1, y);
			return true;
			break;
		case 'S':
		case '+':
			find = ( dfs(x, y+1) | dfs(x+1, y) | dfs(x, y-1) | dfs(x-1, y) );
			acs_num += (find ^ acs[x][y]);
			acs[x][y] = find;
			return find;
		case '-':
			find = ( dfs(x, y+1) | dfs(x, y-1) );
			acs_num += (find ^ acs[x][y]);
			acs[x][y] = find;
			return find;
		case '|':
			find =  ( dfs(x+1, y) | dfs(x-1, y) );
			acs_num += (find ^ acs[x][y]);
			acs[x][y] = find;
			return find;
		case '.':
			find = dfs(x+1, y);
			acs_num += (find ^ acs[x][y]);
			acs[x][y] = find;
			return find;
		default:
			return false;
	}
		
}


int main()
{
	memset(acs, false, sizeof(acs));
	
	cin >> r >> c;
	for (int i=0; i<r; i++) cin >> pic[i];
	
	int s_x, s_y;
	get_start_pos(s_x, s_y);
	
	int pre = 0;
	acs_num = tot = 0;
	while (true)
	{
		memset(vis, false, sizeof(vis));
		dfs(s_x, s_y);
		if (acs_num == pre) break;
		pre = acs_num;
	}

	for (int i=0; i<r; i++)	 for (int j=0; j<c; j++) if (vis[i][j]) { tot++; }
	
	if (acs_num == 0) {
		cout << "I'm stuck!\n";
	} else {
		cout << tot - acs_num << '\n';
	}
	
	return 0;
}

// !! 应使用非短路的 或  '|' 
