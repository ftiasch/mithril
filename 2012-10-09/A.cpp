#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG 0

int counter[26];

string answer;
int try_times;

bool interact(string s) {
    if (DEBUG) {
        try_times ++;
    }
    cout << s << endl << flush;
    if (DEBUG) {
        for (int i = 0, j = 0; i < (int)s.size(); ++ i) {
            if (s[i] == '*') {
                continue;
            }
            while (j < (int)answer.size() && s[i] != answer[j]) {
                j ++;
            }
            if (j >= (int)answer.size()) {
                return false;
            }
            j ++;
        }
        return true;
    }
    string result;
    cin >> result;
    if (result == "Exit") {
        exit(0);
    }
    return result != "No";
}

int main() {
    if (DEBUG) {
        srand(time(0));
        for (int i = 0; i < 10; ++ i) {
            answer += 'a' + rand() % 3;
        }
    }
    memset(counter, 0, sizeof(counter));
    for (int i = 0; i < 26; ++ i) {
        while (true) {
            string query = "*";
            for (int k = 0; k <= counter[i]; ++ k) {
                query += 'a' + i;
                query += "*";
            }
            if (!interact(query)) {
                break;
            }
            counter[i] ++;
        }
    }
    string result;
    for (int i = 0; i < 26; ++ i) {
        int o = 0;
        while (counter[i] > 0) {
            int low = 0;
            int high = (int)result.size();
            while (low < high) {
                int middle = (low + high + 1) >> 1;
                string query = "*";
                int need = o;
                for (int k = 0; k < middle; ++ k) {
                    if (result[k] == 'a' + i) {
                        need --;
                    }
                    query += result[k];
                    query += "*";
                }
                query += ('a' + i);
                query += "*";
                for (int k = 0; k < need; ++ k) {
                    query += ('a' + i);
                    query += '*';
                }
                if (interact(query)) {
                    low = middle;
                } else {
                    high = middle - 1;
                }
            }
            string newResult;
            for (int k = 0; k < (int)result.size() + 1; ++ k) {
                if (k < low) {
                    newResult += result[k];
                } else if (k == low) {
                    newResult += ('a' + i);
                } else {
                    newResult += result[k - 1];
                }
            }
            result = newResult;
            o ++;
            counter[i] --;
        }
    }
    interact(result);
    if (DEBUG) {
        assert(result == answer && try_times <= 75);
    }
    return 0;
}
