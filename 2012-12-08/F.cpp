#include <cstdio>
#include <cstring>

using namespace std;

int n, q, id[256];

char letters[37], buffer[44];
char shapes[36][16][43];

bool valid[36];

int main() {
    scanf("%d%d%s", &n, &q, letters);
    for (int i = 0; i < n; ++ i) {
        id[letters[i]] = i;
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 17; ++ j) {
            scanf("%s", buffer);
            if (j < 16) {
                for (int k = 0; k < 43; ++ k) {
                    shapes[i][j][k] = buffer[k];
                }
            }
        }
    }
    for (int _ = 0; _ < q; ++ _) {
        scanf("%s", buffer);
        int m = strlen(buffer);
        memset(valid, 0, sizeof(valid));
        for (int i = 0; i < 16; ++ i) {
            for (int j = 0; j < 43; ++ j) {
                int counter = 0;
                for (int k = 0; k < m; ++ k) {
                    if (shapes[id[buffer[k]]][i][j] == '*') {
                        counter ++;
                    }
                }
                if (counter == 1) {
                    for (int k = 0; k < m; ++ k) {
                        if (shapes[id[buffer[k]]][i][j] == '*') {
                            valid[k] = true;
                        }
                    }
                }
            }
        }
        printf("Query %d: ", _ + 1);
        for (int i = 0; i < m; ++ i) {
            putchar(valid[i] ? 'Y' : 'N');
        }
        puts("");
    }
    return 0;
} 
