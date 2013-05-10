#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>

using std::string;

int n, w, h, p;
char buffer[22];
std::map <string, bool> visit;
std::map <string, int> factors;

void say(double rate) {
//printf("%.8f\n", rate);
    if (rate < log(10)) {
        puts("Slideshow");
    } else if (rate >= log(60)) {
        puts("Perfect");
    } else {
        puts("So-so");
    }
}

int main() {
    scanf("%d", &n);
    double rate = 0.0;
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        scanf("%d", &factors[buffer]);
        visit[buffer] = true;
        rate -= log(factors[buffer]);
    }
    scanf("%d%d%d", &w, &h, &p);
    rate += log(p) - log(w) - log(h);
    int m ;
    scanf("%d", &m);
    say(rate);
    while (m --) {
        scanf("%s", buffer);
        char oper = buffer[1];
        if (oper == 'f') {
            scanf("%s", buffer);
            if (!visit[buffer]) {
                continue;
            }
            visit[buffer] = false;
            rate += log(factors[buffer]);
        } else if (oper == 'n') {
            scanf("%s", buffer);
            if (visit[buffer]) {
                continue;
            }
            visit[buffer] = true;
            rate -= log(factors[buffer]);
        } else if (oper == 'e') {
            rate += log(w) + log(h);
            scanf("%d%d", &w, &h);
            rate -= log(w) + log(h);
        }
        say(rate);
    }
    return 0;
}
