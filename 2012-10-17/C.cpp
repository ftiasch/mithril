#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

const int M = 10;
const unsigned long long MAGIC = 37;

int n, m, answer;
string source, target;
vector <vector <int> > permutations;

unsigned long long getHash(const string &s) {
    assert((int)s.size() == n);
    unsigned long long result = 0;
    for (int i = 0; i < n; ++ i) {
        result = result * MAGIC + s[i] - 'a';
    }
    return result;
}

string permute(const string &s, const vector <int> &p) {
    assert((int)s.size() == n);
    string t(s);
    int m = (int)p.size();
    if (m > 1) {
        for (int i = 0; i + 1 < m; ++ i) {
            t[p[i + 1]] = s[p[i]];
        }
        t[p[0]] = s[p[m - 1]];
    }
    return t;
}

const int LENGTH = 3214567;
const int SIZE = 1000000;

struct HashTable {
    int size, head[LENGTH], value[SIZE], next[SIZE], predecessor[SIZE];
    unsigned long long key[SIZE];

    HashTable(): size(0) {
        memset(head, -1, sizeof(head));
    }

    int insert(unsigned long long h, int v, int p) {
        int hl = h % LENGTH;
        for (int iter = head[hl]; iter != -1; iter = next[iter]) {
            if (key[iter] == h) {
                return value[iter];
            }
        }
        key[size] = h;
        value[size] = v;
        predecessor[size] = p;
        next[size] = head[hl];
        head[hl] = size ++;
        return -1;
    }

    int query(unsigned long long h) {
        int hl = h % LENGTH;
        for (int iter = head[hl]; iter != -1; iter = next[iter]) {
            if (key[iter] == h) {
                return predecessor[iter];
            }
        }
        assert(false);
    }
};

int finalAnswer;

struct Player {
    static HashTable hash;

    int level, sign;
    vector <vector <int> > permutations;
    queue <string> *opened;
	
	Player(const Player &o): level(o.level), sign(o.sign), permutations(o.permutations) {
		opened = new queue <string>(*(o.opened));
	}

    Player(int sign, const string &source): level(0), sign(sign) {
        opened = new queue <string>();
        opened->push(source);
        hash.insert(getHash(source), sign, 0);
    }

    void add(const vector <int> &p) {
        permutations.push_back(p);
    }

    string expand() {
        level += 2;
        queue <string> *closed = opened;
        opened = new queue <string>();
        while (!closed->empty()) {
            string s = closed->front();
            closed->pop();
            for (int i = 0; i < m; ++ i) {
                string t = permute(s, permutations[i]);
//printf("%s -> %s\n", s.c_str(), t.c_str());
                unsigned long long h = getHash(t);
                int ret = hash.insert(h, level | sign, i);
                if (ret == -1) {
                    opened->push(t);
                } else if ((ret & 1) ^ sign) {
                    finalAnswer = sign ? answer - (level >> 1) : (level >> 1);
                    if (!sign) {
                        finalAnswer --;
                        return s;
                    }
                    return t;
                }
            }
        }
        return "";
    }

    int size() const {
        return opened->size();
    }
};

HashTable Player::hash;

int main() {
    freopen("general.in", "r", stdin);
    freopen("general.out", "w", stdout);
    cin >> n >> m >> source >> target;
    permutations.resize(n);
    Player* forward = new Player(0, source);
    Player* backward = new Player(1, target);
    for (int i = 0; i < m; ++ i) {
        vector <int> &permutation = permutations[i];
        int k;
        scanf("%d", &k);
        while (k --) {
            int position;
            scanf("%d", &position);
            permutation.push_back(-- position);
        }
        forward->add(permutation);
        reverse(permutation.begin(), permutation.end());
        backward->add(permutation);
    }
    answer = 0;
    string middle;
    while (answer < 10) {
        answer ++;
        Player bf=*forward;
        Player *now = forward->size() < backward->size() ? forward : backward;
        string ret = now->expand();
        if (!ret.empty()) {
            middle=bf.expand();
            break;
        }
    }
    if (!middle.empty()) {
        deque <int> result;
        string s = middle;
assert(!(Player::hash.insert(getHash(s), 0, 0) & 1));
//printf("%s\n", middle.c_str());
        while (s != source) {
            int p = Player::hash.query(getHash(s));
//printf("%d\n", p);
            result.push_front(p + 1);
            string t = permute(s, permutations[p]);
//printf("%s <= %s\n", s.c_str(), t.c_str());
            s = t;
        }
        for (int i = 0; i < n; ++ i) {
            reverse(permutations[i].begin(), permutations[i].end());
        }
        s = middle;
        int now = finalAnswer;
        while (s != target) {
            for (int i = 0; i < m; ++ i) {
                string t = permute(s, permutations[i]);
                unsigned long long h = getHash(t);
                int ret = Player::hash.insert(h, 0, 0);
                if (ret != -1 && (ret & 1)) {
                    int step = answer - (ret >> 1);
                    if (now + 1 == step) {
                        result.push_back(i + 1);
                        s = t;
                        break;
                    }
                }
            }
            now ++;
        }
        for (int i = 0; i < (int)result.size(); ++ i) {
            printf("%d%c", result[i], i + 1 == (int)result.size() ? '\n' : ' ');
        }
    } else {
        puts("IMPOSSIBLE");
    }
    return 0;
}
