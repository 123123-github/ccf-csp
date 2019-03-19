#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 108;

int n, m;
string p[maxn], r[maxn];
vector<string> ans;

bool match(const string& p, const string& q)
{
	ans.clear();
	int pl = p.length(), ql = q.length();
	
	int i, j;
	for (i=0, j=0; i<pl && j<ql; i++, j++) {
		if (p[i] != '<' && p[i] == q[j]) continue;
		if (p[i] != '<' && p[i] != q[j]) return false;
		
		int jj = j;
		if (p[i+1] == 'i') {			// <int>
			while (q[j] == '0') j++;
			while ( isdigit(q[jj]) ) jj++;
			i += 4;
		} else if (p[i+1] == 'p') {		// <path>
			jj = ql; 
			i += 5;
		} else {						// <str>			
			while ( q[jj] != '/' ) jj++;
			i += 4;
		}
		ans.push_back(q.substr(j, jj-j));
		j = jj - 1;
	}
	
	if (i >= pl && j >= ql) return true;
	
	else return false;
}

int main()
{
	cin >> n >> m;
	for (int i=0; i<n; i++) cin >> p[i] >> r[i];
	
	string q;
	while (m--)
	{
		cin >> q;
		bool find = false;
		for (int i=0; i<n; i++) {
			if (match(p[i], q)) {
				cout << r[i] << ' ';
				for (int k=0; k<ans.size(); k++) cout << ans[k] << ' ';
				cout << '\n';
				find = true;
				break;
			}
		}
		
		if (!find) cout << "404\n"; 
	}
	
	return 0;
}
