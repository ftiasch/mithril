#include <cstdio>
#include <cstring>
#include <cctype>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 10000;

char buffer[N];

int target, value[N + 1];
std::vector <int> roots;

int main() {
    int test_count;
    gets(buffer);
    sscanf(buffer, "%d", &test_count);
    while (test_count --) {
        gets(buffer);
        for (int i = 0; buffer[i]; ++ i) {
            if (buffer[i] == '=') {
                buffer[i] = 0;
                break;
            }
            if (!isdigit(buffer[i])) {
                buffer[i] = ' ';
            }
        }
        roots.clear();
        std::istringstream sin(buffer);
        while (sin >> target) {
            roots.push_back(target);
        }
        gets(buffer);
        sscanf(buffer, "%d", &target);
        std::sort(roots.begin(), roots.end());
        for (int i = 0, j = 0; i <= N; ++ i) {
            while (j < (int)roots.size() && roots[j] < i) {
                j ++;
            }
            if (j < (int)roots.size() && roots[j] == i) {
                value[i] = 0;
            } else {
                value[i] = j & 1 ? -1 : 1;
            }
        }
        int answer = 0;
        std::vector <std::pair <int, int> > ranges;
        for (int i = 0; i < target; ++ i) {
            int j = 2 * target - i;
            if (j <= N && value[i] * value[j] < 0) {
                answer ++;
                ranges.push_back(std::make_pair(i, j));
            }
        }
        for (int _ = 0; _ < 6; ++ _) {
            std::vector <std::pair <int, int> > new_ranges;
            foreach (iter, ranges) {
                int x = iter->first * 2 - iter->second;
                if (x >= 0 && value[x] * value[iter->first] > 0 && value[x] * value[iter->second] < 0) {
                    new_ranges.push_back(std::make_pair(x, iter->second));
                }
                x = iter->second * 2 - iter->first;
                if (x <= N && value[iter->first] * value[iter->second] < 0 && value[iter->first] * value[x] < 0) {
                    new_ranges.push_back(std::make_pair(iter->first, x));
                }
            }
            answer += (int)new_ranges.size();
            ranges = new_ranges;
        }
        printf("%d\n", answer);
    }
    return 0;
}
