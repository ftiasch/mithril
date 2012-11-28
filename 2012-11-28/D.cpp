#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>

int suits, ranks;

struct Card
{
	int suit, rank;

	void read() {
		static char str[100];
		scanf("%s %d", str, &rank);
		suit = *str - 'A';
		rank --;
	}
};

bool byRank(const Card &a, const Card &b)
{
	return a.rank < b.rank;
}

int getScore(Card *cards)
{
	std::sort(cards, cards + 5, byRank);
	bool isFlush = true, isStraight = true;
	for (int i = 1; i < 5; i++) {
		if (cards[i].suit != cards[0].suit) {
			isFlush = false;
		}
		if (cards[i].rank != cards[i-1].rank + 1) {
			isStraight = false;
		}
	}
	static int cnt[5];
	int sz = 0;
	for (int i = 0; i < 5; ) {
		int ni = i + 1;
		while (ni < 5 && cards[i].rank == cards[ni].rank) {
			ni ++;
		}
		cnt[sz++] = ni - i;
		i = ni;
	}
	std::sort(cnt, cnt + sz);
	std::reverse(cnt, cnt + sz);
	if (cnt[0] == 5) {
		return 10;
	} else if (isFlush && isStraight) {
		return 9;
	} else if (cnt[0] == 4) {
		return 8;
	} else if (cnt[0] == 3 && cnt[1] == 2) {
		return 7;
	} else if (isFlush) {
		return 6;
	} else if (isStraight) {
		return 5;
	} else if (cnt[0] == 3) {
		return 4;
	} else if (cnt[0] == 2 && cnt[1] == 2) {
		return 3;
	} else if (cnt[0] == 2) {
		return 2;
	}
	return 1;
}

int n, m;

const int maxn = 100;
const int maxm = maxn * 10;

Card cards[maxm];
int score[maxn][maxm+1][6];
int prefix[maxn+1][maxm+1];
int suffix[maxn+1][maxm+1];

int cntbit[1 << 5];

void update(int &a, int v)
{
	if (a < v) {
		a = v;
	}
}

int main()
{
	for (int i = 1; i < 1 << 5; i++) {
		cntbit[i] = cntbit[i >> 1] + (i & 1);
	}
	while (scanf("%d%d%d", &n, &suits, &ranks) == 3) {
		m = n * 5;
		for (int i = 0; i < m * 2; i++) {
			cards[i].read();
		}
		memset(score, -1, sizeof(score));
		for (int i = 0; i < n; i++) {
			for (int msk = 0; msk < 1 << 5; msk++) {
				static Card five[5];
				for (int j = 0; j + cntbit[msk] <= m; j++) {
					memcpy(five, cards + i * 5, sizeof(Card) * 5);
					for (int k = 0, z = m + j; k < 5; k++) {
						if (msk >> k & 1) {
							five[k] = cards[z++];
						}
					}
					update(score[i][j][cntbit[msk]], getScore(five));
				}
			}
		}
		memset(prefix, -1, sizeof(prefix));
		memset(suffix, -1, sizeof(suffix));
		prefix[0][0] = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= m; j++) {
				if (prefix[i][j] >= 0) {
					for (int k = 0; k <= 5 && j + k <= m; k++) {
						update(prefix[i + 1][j + k], std::max(prefix[i][j], score[i][j][k]));
					}
				}
			}
		}
		for (int i = 0; i <= m; i++) {
			suffix[n][i] = 0;
		}
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j <= m; j++) {
				if (suffix[i + 1][j] >= 0) {
					for (int k = 0; k <= 5 && j - k >= 0; k++) {
						update(suffix[i][j - k], std::max(suffix[i + 1][j], score[i][j - k][k]));
					}
				}
			}
		}
		bool win = false;
		for (int mypos = 0; mypos < n; mypos++) {
			bool winAllCase = true;
			for (int i = 0; i <= m; i++) {
				if (prefix[mypos][i] >= 0) {
					bool win5 = false;
					for (int j = 0; j <= 5 && i + j <= m; j++) {
						int myscore = score[mypos][i][j];
						if (myscore > prefix[mypos][i] && myscore > suffix[mypos + 1][i + j]) {
							win5 = true;
						}
					}
					if (!win5) {
						winAllCase = false;
					}
				}
			}
			if (winAllCase) {
				win = true;
			}
		}
		puts(win ? "Yes" : "No");
	}
}
