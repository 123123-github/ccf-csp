// 201612-2
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6 + 5;
int T[maxn];

void init()
{
	int s, pre;
	for (s=0; s<=3500; s+=100) T[s] = s;
	
	for (pre=T[s-100]; s<=5000; s+=100) T[s] = pre + (s-3500)/100*97;
	for (pre=T[s-100]; s<=8000; s+=100) T[s] = pre + (s-5000)/10*9;
	for (pre=T[s-100]; s<=12500; s+=100) T[s] = pre + (s-8000)/10*8;
	for (pre=T[s-100]; s<=38500; s+=100) T[s] = pre + (s-12500)/4*3;
	for (pre=T[s-100]; s<=58500; s+=100) T[s] = pre + (s-38500)/10*7;
	for (pre=T[s-100]; s<=83500; s+=100) T[s] = pre + (s-58500)/100*65;
	for (pre=T[s-100]; s<=maxn; s+=100) T[s] = pre + (s-83500)/100*55;
}

int main()
{
	init();
	
	int t;
	cin >> t;
	
	int s; for (s=0; T[s]!=t; s+=100);
	cout << s << '\n';
	
	return 0;
}
