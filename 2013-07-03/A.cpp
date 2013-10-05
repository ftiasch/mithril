#include <cstdio>
#include <cstring>

int readCode(const char *str)
{
	if (str[0] == '0') {
		return -1;
	}
	return (str[0] - 'A') * 2 + (str[1] == '+' ? 1 : 0);
}

const int maxn = 52 * 2;

bool conn[maxn][maxn];

int n;
int input[40000][4];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		static char line[16];
		scanf("%s", line);
		for (int j = 0; j < 4; j++) {
			input[i][j] = readCode(line + j * 2);
		}
		for (int j = 0; j < 4; j++) {
			if (input[i][j] >= 0) {
				for (int k = 1; k <= 3; k++) {
					if (input[i][j + k & 3] >= 0) {
						for (int z = 0; z < 2; z++) {
							conn[(input[i][j] ^ 1) * 2 + z][input[i][j + k & 3] * 2 + (z ^ (k == 2 ? 0 : 1))] = true;
						}
					}
				}
			}
		}
	}
	for (int k = 0; k < maxn; k++) {
		for (int i = 0; i < maxn; i++) {
			for (int j = 0; j < maxn; j++) {
				if (conn[i][k] && conn[k][j]) {
					conn[i][j] = true;
				}
			}
		}
	}
	bool found = false;
	for (int i = 0; i < maxn; i++) {
		if (conn[i][i]) {
			found = true;
		}
	}
	puts(found ? "unbounded" : "bounded");
}
