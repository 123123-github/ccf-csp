#include <cstdio>
#include <cstring>

int ans = 0;
int R, Y, G;

int main()
{
	scanf("%d%d%d", &R, &Y, &G);
	
	int T, k, t;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &k, &t);
		switch (k) {
		case 0: ans += t; break;		// road
		case 1: ans += t; break; 		// red
		case 2: ans += t + R; break;	// yellow
		case 3: break;
		default: break;
		}
	}

	printf("%d\n", ans);
	
	return 0;
}
