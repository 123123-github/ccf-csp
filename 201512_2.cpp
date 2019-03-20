#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 35;

int n, m;
int pic[maxn][maxn];
bool rm[maxn][maxn];

void check_row(const int r)
{
	int b = 0, e = 0;		// begin & end
	while (e < m) {			// row --> M
		while (e < m && pic[r][e] == pic[r][b]) e++;
		if (e - b >= 3) for (int j=b; j<e; j++) rm[r][j] = true;
		b = e;
	}
}

void check_col(const int c)
{
	int b = 0, e = 0;		// begin & end
	while (e < n) {			// col --> N
		while (e < n && pic[e][c] == pic[b][c]) e++;
		if (e - b >= 3) for (int i=b; i<e; i++) rm[i][c] = true;
		b = e;
	}
}

int main()
{
	memset(rm, false, sizeof(rm));
	
	cin >> n >> m;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			cin >> pic[i][j];
		}
	}
	
	for (int i=0; i<n; i++) check_row(i);
	for (int j=0; j<m; j++) check_col(j);
	
	int num;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			num = rm[i][j]? 0: pic[i][j];
			cout << num << ' ';
		}
		cout << '\n';
	}
	
	return 0;}
