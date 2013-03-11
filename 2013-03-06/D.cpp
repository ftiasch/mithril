#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int N = 9;
const char NUMBER = 0;

const char chars[N + 1] = "\"^'=~-,._";
const int multi[N] = {24, 20, 18, 14, 12, 8, 6, 4, 3};

const int buffer_size = 1 << 20;

char buffer[buffer_size];
int size = 0;

long long MAXV = 1;

vector<long long> numbers;
vector<bool> flag;

int next_char = 0;

bool isdipus(char ch)
{
    for (int i = 0; i < N; i++) {
        if (chars[i] == ch) {
            return true;
        }
    }
    return false;
}

int getc()
{
    char ret = next_char;
    next_char = getchar();
    return ret;
}

long long getDigit()
{
    if (next_char == '0') {
        getc();
        return 0;
    }
    long long ret = 0;
    while (isdigit(next_char) && ret * 10 + next_char - '0' <= MAXV) {
        ret = ret * 10 + getc() - '0';
    }
    return ret;
}

long long getDipus()
{
    if (next_char == 79) {
        getc();
        return 0;
    }
    long long ret = 0;
    for (int i = 0; i < N; i++) {
        ret *= multi[i];
        for (int j = 1; j < multi[i]; j++) {
            if (next_char == chars[i]) {
                getc();
                ret ++;
            }
        }
    }
    return ret;
}

void printDigit(long long a)
{
    printf("%lld", a);
}

void printDipus(long long a)
{
    if (a == 0) {
        putchar(79);
        return;
    }
    static char buf[1 << 10];
    int ptr = 0;
    for (int i = N - 1; i >= 0; i--) {
        int mod = a % multi[i];
        for (int j = 0; j < mod; j++) {
            buf[ptr++] = chars[i];
        }
        a /= multi[i];
    }
    buf[ptr] = '\0';
    reverse(buf, buf + ptr);
    printf("%s", buf);
}

int main()
{
    for (int i = 0; i < N; i++) {
        MAXV *= multi[i];
    }
    MAXV --;
    next_char = getchar();
    while (next_char >= 0) {
        if (isdigit(next_char)) {
            flag.push_back(true);
            numbers.push_back(getDigit());
            buffer[size++] = NUMBER;
        } else if (isdipus(next_char) || next_char == 79) {
            flag.push_back(false);
            numbers.push_back(getDipus());
            buffer[size++] = NUMBER;
        } else {
            buffer[size++] = getc();
        }
    }
    if (numbers.size() % 2 == 1) {
        sort(numbers.begin(), numbers.end());
    }
    int ptr = 0;
    for (int i = 0; i < size; i++) {
        if (buffer[i] == NUMBER) {
            if (flag[ptr]) {
                printDipus(numbers[ptr]);
            } else {
                printDigit(numbers[ptr]);
            }
            ptr ++;
        } else {
            putchar(buffer[i]);
        }
    }
}
