#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int pic[3][3];
int opnt[] = { 0, 2, 1 };
int vis[3][5][10];

inline bool is_win(int p)
{
	for (int i=0; i<3; i++) if (vis[p][0][i]==3 || vis[p][1][i]==3) return true;
	if (vis[p][2][2]==3 || vis[p][3][2]==3) return true;
	return false;
}

void pre_deal()
{
	memset(vis, 0, sizeof(vis));
	for (int r=0; r<3; r++) for (int c=0; c<3; c++) if (pic[r][c]) {
			int p = pic[r][c];
			vis[p][0][r]++; vis[p][1][c]++;
			vis[p][2][r+c]++; vis[p][3][r-c+2]++;
			vis[0][0][0]++;
	}	
}

// Alpha-Beta
int min_max(int p, int alpha, int beta)
{
	if ( is_win(opnt[p]) ) {
		int score = 9 - vis[0][0][0] + 1;
		return (p==1? -score: score);
	}
	if ( vis[0][0][0]==9 ) return 0;
	
	// foreach next state
	for (int i=0; i<3; i++) for (int j=0; j<3; j++) if (!pic[i][j]) {
		vis[p][0][i]++; vis[p][1][j]++; vis[p][2][i+j]++; vis[p][3][i-j+2]++;
		vis[0][0][0]++; 
		pic[i][j] = p;
		int t = min_max(opnt[p], alpha, beta);
		pic[i][j] = 0;
		vis[0][0][0]--; 
		vis[p][0][i]--; vis[p][1][j]--; vis[p][2][i+j]--; vis[p][3][i-j+2]--;
		
		if (p==1) alpha = max(alpha, t);
		else beta = min(beta, t);
		if (alpha >= beta) break;
	}
	
	return p==1? alpha: beta;
}

int main()
{
	int T; cin >> T;
	while (T--)
	{
		// get pic
		for (int i=0; i<3; i++) for (int j=0; j<3; j++) cin >> pic[i][j];
		// get cur state
		pre_deal();
		
		cout << min_max(1, -100, 100) << '\n';
	}
	
	return 0;
}
