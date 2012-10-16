#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

const int N = 100000;
const int INF = 1000000000;

char text[N + 1];
int maximum[N][2][2];

void update(int &x, int a) {
    x = max(x, a);
}

int main() {
    scanf("%s", text);
    int nodeCount = 0;
    maximum[0][0][0] = 0;
    maximum[0][0][1] = maximum[0][1][0] = 1;
    maximum[0][1][1] = -INF;
    nodeCount ++;
    vector <int> stack;
    for (int p = strlen(text) - 1; p >= 0; -- p) {
        if (text[p] == 'g') {
            stack.push_back(0);
        } else {
            int a = stack.back();
            stack.pop_back();
            int b = stack.back();
            stack.pop_back();
            for (int i = 0; i < 2; ++ i) {
                for (int j = 0; j < 2; ++ j) {
                    maximum[nodeCount][i][j] = -INF;
                }
            }
            if (text[p] == 'S') {
                for (int i = 0; i < 2; ++ i) {
                    for (int j = 0; j < 2; ++ j) {
                        for (int k = 0; k < 2; ++ k) {
                            update(maximum[nodeCount][i][k], maximum[a][i][j] + maximum[b][j][k] - j);
                        }
                    }
                }
            } else {
                for (int i = 0; i < 2; ++ i) {
                    for (int j = 0; j < 2; ++ j) {
                        update(maximum[nodeCount][i][j], maximum[a][i][j] + maximum[b][i][j] - i - j);
                    }
                }
            }
            stack.push_back(nodeCount);
            nodeCount ++;
        }
    }
    int result = 0;
    int a = stack.back();
    for (int i = 0; i < 2; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            update(result, maximum[a][i][j]);
        }
    }
    printf("%d\n", result);
    return 0;
}
