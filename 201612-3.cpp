#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 108;

vector<string> u_name, r_name, p_name;
map<string, int> u_id, r_id, p_id;
vector<int> u_list[maxn], r_list[maxn], rl_list[maxn], p_level;

void sep(const string& priv, string& pname, int& plevel)
{
	int len = priv.length();
	if (len > 2 && priv[len-2] == ':') {
		pname = priv.substr(0, len-2);
		plevel = priv[len-1] - '0';
	}
	else
	{
		pname = priv;
		plevel = -1;
	}
}

void get_data()
{
	int p, r, u, plevel;
	string priv, pname, rname, uname;
	
	cin >> p;
	for (int i=0; i<p; i++) {
		cin >> priv; sep(priv, pname, plevel);
		// add pri
		p_name.push_back(pname);
		p_id[pname] = i;
		p_level.push_back(plevel);
	}
	
	cin >> r;
	for (int i=0; i<r; i++) {
		cin >> rname >> p;
		// add role
		r_name.push_back(rname);
		r_id[rname] = i;
		// set r_list
		for (int k=0; k<p; k++) {
			cin >> priv; sep(priv, pname, plevel);
			r_list[i].push_back( p_id[pname] );
			rl_list[i].push_back( plevel );
		}
	}
	
	cin >> u;
	for (int i=0; i<u; i++) {
		cin >> uname >> r;
		// add user
		u_name.push_back(uname);
		u_id[uname] = i;
		// set u_list
		for (int k=0; k<r; k++) {
			cin >> rname;
			u_list[i].push_back( r_id[rname] );
		}
	}
}

bool find(const string& uname, const string& pname, int dst_plevel, int& r_plevel)
{
	r_plevel = -1;
	if (!u_id.count(uname) || !p_id.count(pname)) return false;
	
	bool find = false;
	int uid = u_id[uname], dst_pid = p_id[pname];
	const vector<int>& ulist = u_list[uid];
	for (int i=0; i<ulist.size(); i++) {
		int rid = ulist[i];
		const vector<int>& rlist = r_list[rid];
		const vector<int>& rllist = rl_list[rid];
		for (int k=0; k<rlist.size(); k++) {
			int pid = rlist[k];
			int plevel = rllist[k];
			if (pid == dst_pid && dst_plevel <= plevel) {
				r_plevel = max(r_plevel, plevel);
				find = true;
			}
		}
	}
	
	return find;
}

int main()
{	
	get_data();
	
	int q, plevel, r_plevel; cin >> q;
	string uname, pname, priv;
	while (q--)
	{
		cin >> uname >> priv;
		sep(priv, pname, plevel);
		
		if ( find(uname, pname, plevel, r_plevel) ) {
			// cout << r_plevel << '\n';
			if (plevel == -1 && r_plevel != -1) cout << r_plevel << '\n';
			else cout << "true\n";
		}
		else {
			cout << "false\n";
		}
	}
	
	return 0;
}
