#include <cstdio>
#include <cstring>
using namespace std;

const int N = 10000;

char a[N], b[N];

int main() {
    scanf("%s%s", a, b);
    puts(strlen(a) < strlen(b) ? "no" : "go");
    return 0;
}
