#include <cstring>
#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef long long LL;

const int maxn = 25;

int day_of_month[2][13] = { {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} };
inline bool is_leap_year(int y) { return ( (y%4==0 && y%100!=0) || y%400==0 ); }
int week[2100][15][35];

map<string, string> map_mon_week;

struct Time
{
	int yyyy, mm, dd, HH, MM;
	
	Time(LL x)
	{
		MM = x % 100; x /= 100;
		HH = x % 100; x /= 100;
		dd = x % 100; x /= 100;
		mm = x % 100; x /= 100;
		yyyy = x;
	}
	
	void operator++() {
		if (MM < 59) { MM++; return; }
		MM = 0; if (HH < 23) { HH++; return; }
		HH = 0; if (dd < day_of_month[is_leap_year(yyyy)][mm]) { dd++; return; }
		dd = 1; if (mm < 12) { mm++; return; }
		mm = 1; yyyy++;
	}
	
	bool operator<(const Time& rhs) const {
		if (yyyy != rhs.yyyy) return yyyy < rhs.yyyy;
		if (mm != rhs.mm) return mm < rhs.mm;
		if (dd != rhs.dd) return dd < rhs.dd;
		if (HH != rhs.HH) return HH < rhs.HH;
		return MM < rhs.MM;
	}
	
};

struct Command
{
	int MM[60], HH[24];
	int dd[32], mm[13], week[7];
	string str;
} cmds[maxn];

void init()
{   
	// set map
	map_mon_week["jan"] = "1"; map_mon_week["feb"] = "2"; map_mon_week["mar"] = "3"; map_mon_week["apr"] = "4";
	map_mon_week["may"] = "5"; map_mon_week["jun"] = "6"; map_mon_week["jul"] = "7"; map_mon_week["aug"] = "8";
	map_mon_week["sep"] = "9"; map_mon_week["oct"] = "10"; map_mon_week["nov"] = "11"; map_mon_week["dec"] = "12";
	map_mon_week["sun"] = "0"; map_mon_week["mon"] = "1"; map_mon_week["tue"] = "2"; map_mon_week["wed"] = "3";
	map_mon_week["thu"] = "4"; map_mon_week["fri"] = "5"; map_mon_week["sat"] = "6";
	
	// count week
	int y = 1970, m = 1, d = 1, w = 4;
	while (y <= 2099) {
		while (m <= 12) {
			while (d <= day_of_month[is_leap_year(y)][m]) {
				week[y][m][d] = w;
				w = w==6? 0: w+1;
				d++;
			}
			m++; d = 1;
		}
		y++; m = 1;
	}
}

inline bool match(const Time& t, const Command& c)
{
	return ( (c.week[0]==-1 || c.week[ week[t.yyyy][t.mm][t.dd] ] ) && 
	( c.mm[0]==-1 || c.mm[t.mm] ) && 
	( c.dd[0]==-1 || c.dd[t.dd] ) && 
	( c.HH[0]==-1 || c.HH[t.HH] ) && 
	( c.MM[0]==-1 || c.MM[t.MM] ) );
}

// deal with - Mon Jan Feb ...
void deal_str(string& s)
{
	string t1 = "", t2 = "";
	for (int i=0; s[i]; i++) {
		if ( isalpha(s[i]) ) t1.push_back( tolower(s[i]) );
		else {	// NOT alpha
			if (!t1.empty()) { t2.append( map_mon_week[t1] ); t1.clear(); }
			t2.push_back(s[i]);
		}
	}
	if (!t1.empty()) t2.append( map_mon_week[t1] );
	s = t2;
}

// set array value
void get_info(const string& s, int d[])
{
	if (s == "*") { d[0] = -1; return; }
	
	int x = 0, x0 = -1, len = s.length();
	for (int i=0; i<len; i++) {
		if ( isdigit(s[i]) ) {			// DIGIT
			x = x*10 + s[i] - '0';
		}
		else if ( s[i] == ',' ) {		// ','
			if (x0 >= 0) { for (int k=x0; k<=x; k++) d[k] = 1; x0 = -1; }
			else d[x] = 1;
			x = 0;		// !!! 两种情况都要归零 - score 20
		}
		else {							// '-'
			x0 = x; x = 0;
		}
	}
	if (x0 >= 0) { for (int k=x0; k<=x; k++) d[k] = 1; }
	else { d[x] = 1; }

//  Reference
//	int len=s.length();
//    if(s=="*") d[0]=-1;
//    else
//    for(int i=0;i<len;)
//	{
//        int t1=0;
//        while(i<len&&s[i]>='0'&&s[i]<='9'){t1=t1*10+(s[i]-'0');i++;}
//        if(s[i]=='-'){
//            int t2=0;i++;
//            while(i<len&&s[i]>='0'&&s[i]<='9'){t2=t2*10+(s[i]-'0');i++;}
//            for(int t=t1;t<=t2;t++)d[t]=1;
//            i++;
//        }
//        else{
//            d[t1]=1;i++;
//        }
//    }
    
}

int main()
{
	init();
	
	int n; LL s, t;
	cin >> n >> s >> t;
	
	string temp;
	for (int i=0; i<n; i++) {
		cin >> temp; get_info(temp, cmds[i].MM);
		cin >> temp; get_info(temp, cmds[i].HH);
		cin >> temp; get_info(temp, cmds[i].dd);
		cin >> temp; deal_str(temp); get_info(temp, cmds[i].mm);
		cin >> temp; deal_str(temp); get_info(temp, cmds[i].week);
		cin >> cmds[i].str;
	}
	
	Time t_begin(s), t_end(t);
	for (Time time=t_begin; time<t_end; ++time) {
		for (int i=0; i<n; i++) if (match(time, cmds[i])) {
			printf("%04d%02d%02d%02d%02d %s\n", time.yyyy, time.mm, time.dd, time.HH, time.MM, cmds[i].str.c_str());
		}
	}
	
	return 0;
} 

// !!! 缩写 不区分大小写 - 10
// !!! set array value 时两种情况都要归零 - 20