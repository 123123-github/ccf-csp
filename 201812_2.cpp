#include <cstdio>
#include <cstring>

long long int ans = 0;

int k, t;
int R, Y, G;
int past, tot;

int light_len[5];
int next_light[] = {0, 3, 1, 2};
// 1 --> 3 --> 2 --> 1 ...

void pre_del()
{
	tot = R + Y + G;
	light_len[1] = R; light_len[2] = Y; light_len[3] = G;
}

void get_cur()
{
	if (k == 0) return;				// jmp road
	
	past = ans % tot;
	t = t - past;
	while (t <= 0) {
		k = next_light[k];
		t = t + light_len[k];
	}
}

void del_cur()
{
	switch (k) {
	case 0: ans += t; break;		// road
	case 1: ans += t; break; 		// red
	case 2: ans += t + R; break;	// yellow
	case 3: break;
	default: break;
	}
}

int main()
{
	scanf("%d%d%d", &R, &Y, &G);
	pre_del();
	
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &k, &t);		
		get_cur();
		del_cur();
	}

	printf("%lld\n", ans);
	
	return 0;
}

/*
	use LONG LONG !!!
	scanf & printf
*/
