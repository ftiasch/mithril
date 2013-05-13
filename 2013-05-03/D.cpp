#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

const int N = 1000;
const char* SOUNDS[7] = {"C+", "D+", "E", "F", "F+", "G+", "A+"};
const char* ALIAS[7] = {"D-", "E-", "F-", "E+", "G-", "A-", "B-"};

int n, m, a[N], b[N];
char buffer[10];

//int get_id(const char* sound) {
//    for (int i = 0; i < 12; ++ i) {
//        if (strcmp(SOUNDS[i], sound) == 0) {
//            return i;
//        }
//        if (strcmp(ALIAS[i], sound) == 0) {
//            return i;
//        }
//    }
//    assert(false);
//}

//bool equal(const char *a, const char *b) {
//    if (strcmp(a, b) == 0) {
//        return true;
//    }
//
//    if (*a == *b) {
//        for (int i = 0; i < 7; ++ i) {
//            if (strcmp(a + 1, SOUNDS[i]) == 0 && strcmp(b + 1, ALIAS[i]) == 0) {
//                return true;
//            }
//        }
//    }
//    if (*a + 1 == *b) {
//        if (strcmp(a + 1, "B+") == 0 && strcmp(b + 1, "C") == 0) {
//            return true;
//        }
//        if (strcmp(a + 1, "B") == 0 && strcmp(b + 1, "C-") == 0) {
//            return true;
//        }
//    }
//    return false;
//}

void raise(char *s) {
    for (int i = 0; i < 7; ++ i) {
        if (strcmp(s + 1, SOUNDS[i]) == 0) {
            strcpy(s + 1, ALIAS[i]);
            return;
        }
    }
    if (strcmp(s + 1, "B+") == 0) {
        s[0] ++;
        strcpy(s + 1, "C");
        return;
    }
    if (strcmp(s + 1, "B") == 0) {
        s[0] ++;
        strcpy(s + 1, "C-");
        return;
    }
}

int get_id(char *s) {
    raise(s);
    int ret = 0;
    ret += s[0] - '0';
    ret *= 10;
    ret += s[1] - 'A';
    ret *= 2;
    ret += s[2] == '-';
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        a[i] = get_id(buffer);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        scanf("%d", &m);
        for (int i = 0; i < m; ++ i) {
            scanf("%s", buffer);
            b[i] = get_id(buffer);
        }
        int answer = 0;
        for (int offset = -m + 1; offset < n; ++ offset) {
            int count = 0;
            for (int j = std::max(0, -offset); offset + j < n && j < m; ++ j) {
                count += a[offset + j] == b[j];
            }
            answer = std::max(answer, count);
        }
        printf("%.6f\n", (double)answer / m);
    }
    return 0;
}
