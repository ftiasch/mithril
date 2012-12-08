#include <cstdio>
#include <cstring>

const int maxn = 1 << 10;

int n;
double P;

double prob[maxn];

int main()
{
	int tests;
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%lf", &n, &P);
		memset(prob, 0, sizeof(prob));
		prob[0] = 1;
		for (int i = 0; i < n; i++) {
			double np = prob[i];
			if (i > 0) {
				np *= P;
			}
			double oneside = 1.0;
			for (int j = 1; i + j <= n; j++) {
				oneside *= P;
				prob[i + j] += np * (1 - (1 - oneside) * (1 - oneside));
				np *= 1 - P;
			}
		}
		printf("%.10f\n", 1 - prob[n]);
	}
}

