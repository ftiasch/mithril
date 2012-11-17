#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000;

int x, delta[N];
char buffer[N];
vector <int> stack;

int main() {
    scanf("%d%s", &x, buffer);
    int n = strlen(buffer);
    for (int i = 0; i < n; ++ i) {
        delta[i] = buffer[i] == 'M' ? 1 : -1;
    }
    int answer = 0;
    int counter = 0;
    for (int i = n - 1; i >= 0; -- i) {
        stack.push_back(delta[i]);
    }
    while (!stack.empty()) {
        int a = stack.back();
        stack.pop_back();
        if (abs(counter + a) <= x) {
            counter += a;
            answer ++;
        } else if (!stack.empty()) {
            int b = stack.back();
            stack.pop_back();
            stack.push_back(a);
            if (abs(counter + b) <= x) {
                counter += b;
                answer ++;
            } else {
                break;
            }
        }
    }
    printf("%d\n", answer);
    return 0;
}
