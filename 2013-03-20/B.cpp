#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

using std::make_pair;

const int N = 50000;
const int Q = 100000;

char type[Q];
int n, a[N + 1], q, from[Q], to[Q], param[Q];
std::vector <int> values;

int get_value(int value) {
    return std::lower_bound(values.begin(), values.end(), value) - values.begin() + 1;
}

const int M = N + Q + 1;

struct Node {
    int value, count, size;

    Node(int value) : value(value), count(0), size(0) {
    }
};

bool operator <(const Node &a, const Node &b) {
    return a.value < b.value;
}

bool operator ==(const Node &a, const Node &b) {
    return a.value == b.value;
}

typedef std::vector <Node> Array;

int m;
Array elements[M];

void update(Array &array, int key, int delta) {
    int low = 0;
    int high = array.size() - 1;
    while (low <= high) {
        int middle = low + high >> 1;
        array[middle].size += delta;
        if (array[middle].value == key) {
            array[middle].count += delta;
            break;
        }
        if (key < array[middle].value) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
}

Array *current;

int query(int l, int r, int a, int b) {
    if (l > r || b < (*current)[l].value || (*current)[r].value < a) {
        return 0;
    }
    int m = l + r >> 1;
    if (a <= (*current)[l].value && (*current)[r].value <= b) {
        return (*current)[m].size;
    }
    int ret = query(l, m - 1, a, b) + query(m + 1, r, a, b);
    if (a <= (*current)[m].value && (*current)[m].value <= b) {
        ret += (*current)[m].count;
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
        values.push_back(a[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++ i) {
        char buffer[2];
        scanf("%s", buffer);
        type[i] = *buffer;
        if (type[i] == 'g') {
            scanf("%d%d%d", from + i, to + i, param + i);
        } else {
            scanf("%d%d", from + i, param + i);
            values.push_back(param[i]);
        }
    }

    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    m = values.size();
    for (int i = 1; i <= n; ++ i) {
        for (int k = get_value(a[i]); k <= m; k += -k & k) {
            elements[k].push_back(Node(i));
        }
    }
    for (int i = 0; i < q; ++ i) {
        if (type[i] == 's') {
            for (int k = get_value(param[i]); k <= m; k += -k & k) {
                elements[k].push_back(Node(from[i]));
            }
        }
    }
    for (int i = 1; i <= m; ++ i) {
        std::sort(elements[i].begin(), elements[i].end());
        elements[i].erase(std::unique(elements[i].begin(), elements[i].end()), elements[i].end());
    }

    int bound = 0;
    while ((1 << bound + 1) <= m) {
        bound ++;
    }

    for (int i = 1; i <= n; ++ i) {
//printf("%d: \n", i);
        for (int k = get_value(a[i]); k <= m; k += -k & k) {
//printf("%d\n", k);
            update(elements[k], i, 1);
        }
    }

    for (int j = 0; j < q; ++ j) {
        if (type[j] == 's') {
            int i = from[j];
            for (int k = get_value(a[i]); k <= m; k += -k & k) {
                update(elements[k], i, -1);
            }
            a[i] = param[j];
            for (int k = get_value(a[i]); k <= m; k += -k & k) {
                update(elements[k], i, 1);
            }
        } else {
            int answer = 0;
            for (int i = bound; i >= 0; -- i) {
                if (answer + (1 << i) <= m) {
                    current = elements + answer + (1 << i);
                    int size = query(0, (int)current->size() - 1, from[j], to[j]);
                    if (size < param[j]) {
                        param[j] -= size;
                        answer += 1 << i;
                    }
                }
            }
            printf("%d\n", values[answer]);
        }
    }
    return 0;
}
