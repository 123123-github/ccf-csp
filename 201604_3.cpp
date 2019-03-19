#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

char c;
int next_state;
string cur, cur0, x;

void state_0()
{
	if (c == '/') {
		next_state = 0;	
	}
	else if ( isalnum(c) || c=='-' || c=='_') {
		x += c;
		next_state = 1;
	}
	else if (c == '.') {
		next_state = 2;	
	}
	else cout << "error 0";
}

void state_1()
{
	if (isalnum(c) || c=='.' || c=='-' || c=='_') {
		x += c;
		next_state = 1;
	}
	else if (c == '/') {
		x += '/';
		next_state = 0;
	}
	else cout << "error 1";
}

void state_2()
{
	if (c == '/') {
		next_state = 0;
	}
	else if (c == '.') {
		next_state = 3;
	}
	else if (isalnum(c) || c=='-' || c=='_') {
		x = x + '.' + c;
		next_state = 1; 
	}
	else cout << "error 2";
}

void state_3()
{
	if (c == '/') {
		if (x.length()!=1) x.pop_back();
		while (x.back() != '/') x.pop_back();
		next_state = 0;
	}
	else if (isalnum(c) || c=='.' || c=='-' || c=='_') {
		x = x + ".." + c;
		next_state = 1;
	}
	else {
		cout << "error 3";
	}
}

void deal_str(const string& s)
{
	x.clear();
	
	int len = s.length();
	if (len == 0) { x = cur0; return; }
	
	if (s[0] == '/') x += '/';
	else x += cur;
	
	int state = 0, i = 0;
	while (i < len)
	{
		c = s[i++];
		switch(state) {
		case 0: state_0(); break;
		case 1: state_1(); break;
		case 2: state_2(); break;
		case 3:	state_3(); break;
		default:
			cout << "error!\n";
			break;
		}
		
		state = next_state;
	}
	
	if (x.length()!=1 && x.back()=='/') x.pop_back();
}

int main()
{
	int p; cin >> p >> cur; getchar();
	cur0 = cur;
	if (cur.back() != '/') cur += '/';
	
	string temp;
	while (p--)
	{
		getline(cin, temp);
		deal_str(temp);
		cout << x << '\n';
	}
	
	return 0;
}

// c++11 -- string::back()
