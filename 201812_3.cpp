#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int maxn = 100008;

int n;
bool pass[maxn];
struct IP { 
	unsigned int pref, len; 
	bool operator<(const IP& rhs) { return pref!=rhs.pref? pref<rhs.pref: len<rhs.len; }
} ip[maxn];

unsigned int bits[] = {
	0x00000000,
	0x80000000, 0xc0000000, 0xe0000000, 0xf0000000,
	0xf8000000, 0xfc000000, 0xfe000000, 0xff000000,
	0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
	0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000,
	0xffff8000, 0xffffc000, 0xffffe000, 0xfffff000,
	0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
	0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0,
	0xfffffff8, 0xfffffffc, 0xfffffffe, 0xffffffff,
};
unsigned int bits_pos[] = {
	0x0,
	0x80000000, 0x40000000, 0x20000000, 0x10000000,
	0x08000000, 0x04000000, 0x02000000, 0x01000000,
	0x00800000, 0x00400000, 0x00200000, 0x00100000,
	0x00080000, 0x00040000, 0x00020000, 0x00010000,
	0x00008000, 0x00004000, 0x00002000, 0x00001000,
	0x00000800, 0x00000400, 0x00000200, 0x00000100,
	0x00000080, 0x00000040, 0x00000020, 0x00000010,
	0x00000008, 0x00000004, 0x00000002, 0x00000001,
};

void to_bits_ip(int pos, string& s)
{
	int dot = 0, slash = 0;
	for (int i=0; s[i]; i++) {
		if (s[i] == '.') dot++;
		else if (s[i] == '/') slash++;
	}
	
	int a3 = 0, a2 = 0, a1 = 0, a0 = 0, len = 0;
	if (dot == 3 && slash == 1) {
		// standard
		sscanf(s.c_str(), "%d.%d.%d.%d/%d", &a3, &a2, &a1, &a0, &len);
	} else if (slash) {
		// without post
		if (dot == 3) sscanf(s.c_str(), "%d.%d.%d.%d/%d", &a3, &a2, &a1, &a0, &len);
		else if (dot == 2) sscanf(s.c_str(), "%d.%d.%d/%d", &a3, &a2, &a1, &len);
		else if (dot == 1) sscanf(s.c_str(), "%d.%d/%d", &a3, &a2, &len);
		else sscanf(s.c_str(), "%d/%d", &a3, &len);
	} else {
		// without len
		len = ((dot + 1) << 3);
		if (dot == 3) sscanf(s.c_str(), "%d.%d.%d.%d", &a3, &a2, &a1, &a0);
		else if (dot == 2) sscanf(s.c_str(), "%d.%d.%d", &a3, &a2, &a1);
		else if (dot == 1) sscanf(s.c_str(), "%d.%d", &a3, &a2);
		else sscanf(s.c_str(), "%d", &a3);
	}
	
	int t = a3; t = (t<<8) | a2; t = (t<<8) | a1; t = (t<<8) | a0;
	ip[pos].pref = t; ip[pos].len = len;
}

void print_bits_ip(int pos)
{
	int t = ip[pos].pref, len = ip[pos].len;
	cout << ((t >> 24) & 0xff) << '.';
	cout << ((t >> 16) & 0xff) << '.';
	cout << ((t >> 8) & 0xff) << '.';
	cout << (t & 0xff) << '/' << len << '\n';
}

// 2. merge --> subset
bool is_subset(unsigned int a, unsigned int x, unsigned int b) {
	// return !( (a ^ b) & ((-1 >> (32-x)) << (32-x)) );
	return !( (a ^ b) & bits[x] );
}

void ip_size_merge()
{
	for (int i=0; i<n; i++) if (!pass[i]) {
		unsigned int a_ip = ip[i].pref, a_len = ip[i].len;
		for (int j=i+1; j<n; j++) if (!pass[j]) {
			unsigned int b_ip = ip[j].pref, b_len = ip[j].len;
			if (!is_subset(a_ip, a_len, b_ip)) break;
			pass[j] = true;
		}
	}
}

// 3. merge --> same level
bool legal(IP p) {
	if (p.len < 0) return false;
	return !( p.pref & (~bits[p.len]) );
}

bool can_merge(unsigned int a, unsigned int b, unsigned x)
{
	// return (a ^ b) & bits_pos[x]; --> error !!!
	return (a ^ b) == bits_pos[x];
}

void ip_level_merge()
{
	for (int i=0; i<n; i++) if (!pass[i]) {
		unsigned int a_ip = ip[i].pref, a_len = ip[i].len;
		
		for (int j=i+1; j<n; j++) if (!pass[j]) {
			unsigned int b_ip = ip[j].pref, b_len = ip[j].len;
			if (a_len != b_len) break;
			
			IP new_ip = ip[i]; new_ip.len--;
			
			if (legal(new_ip) && can_merge(a_ip, b_ip, a_len)) {
				ip[i] = new_ip;
				pass[j] = true;
				// find pre_pos
				int pre_pos; for (pre_pos=i-1;pre_pos>=0 && pass[pre_pos]; pre_pos--);
				if (pre_pos >= 0) i = pre_pos - 1;
				else i = i-1;
			}
			
			break;
		}
	}
}

int main()
{
	string s;
	
	cin >> n;
	for (int i=0; i<n; i++) {
		cin >> s;
		to_bits_ip(i, s);
	}
	
	sort(ip, ip+n);
	ip_size_merge();
	ip_level_merge();
	
	for (int i=0; i<n; i++) if (!pass[i]) {
		print_bits_ip(i);
	}
	
	return 0;
}