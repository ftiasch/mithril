#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::vector;

const int N = 4000;
const int MAGIC = 100003;

char buffer[(N << 1) + 1];
int match[N << 1];

struct HList {
    unsigned long long hash;
    vector <int> *v;

    HList(int e) {
        hash = e;
        v = new vector<int> ();
        v->push_back(e);
    }

    HList append(int e) {
        hash *= MAGIC;
        hash += e;
        v->push_back(e);
        return *this;
    }

    int back() {
        return v->back();
    }

    HList modify(int e) {
        hash -= v->back();
        hash += e;
        v->back() = e;
        return *this;
    }
};

bool operator <(const HList &a, const HList &b) {
    return a.hash < b.hash;
}

bool operator ==(const HList &a, const HList &b) {
    return a.hash == b.hash;
}

int node_count;
std::vector <HList> lists[N];

int solve(int l, int r) {
    int u = node_count ++;
    lists[u].clear();
    lists[u].push_back(HList(0));
    for (int i = l + 1; i < r; i = match[i] + 1) {
        int v = solve(i, match[i]);
        foreach (iter, lists[v]) {
            lists[u].push_back(iter->append(-1));
        }
    }
    std::vector <HList> &v = lists[u];
    std::sort(v.begin(), v.end());
    for (int i = 0; i < (int)v.size(); ++ i) {
        HList &h = v[i];
        if (h.back() == 0) {
            continue;
        }
        int j = i;
        while (j < (int)v.size() && v[i] == v[j]) {
            j ++;
        }
        int size = 0;
        for (int k = i; k < j; ++ k) {
            v[k].modify(++ size);
        }
        i = j - 1;
    }
    return u;
}

int main() {
    while (scanf("%s", buffer) == 1 && *buffer != '0') {
        int n = strlen(buffer) >> 1;
        std::stack <int> stack;
        for (int i = (n << 1) - 1; i >= 0; -- i) {
            if (buffer[i] == '(') {
                match[i] = stack.top();
                stack.pop();
            } else {
                stack.push(i);
            }
        }
        node_count = 0;
        solve(0, (n << 1) - 1);
        std::vector <std::vector <int> > answer;
        foreach (iter, lists[0]) {
            answer.push_back(*iter->v);
            delete iter->v;
            std::reverse(answer.back().begin(), answer.back().end());
        }
        std::sort(answer.begin(), answer.end());
        foreach (v, answer) {
            for (int i = 0; i < (int)v->size(); ++ i) {
                printf("%d%c", (*v)[i], " \n"[i == (int)v->size() - 1]);
            }
        }
    }
    return 0;
}
