#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

char buffer[10000000];

struct Date {
    int year, month, day;

    Date(int year, int month, int day): year(year), month(month), day(day) {}
};

bool operator ==(const Date &a, const Date &b) {
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

bool operator <(const Date &a, const Date &b) {
    if (a.year == b.year) {
        if (a.month == b.month) {
            return a.day < b.day;
        }
        return a.month < b.month;
    }
    return a.year < b.year;
}

vector <Date> dates;

bool isSeperator(char token) {
    return token == '.' || token == '-' || token == '/';
}

bool isLeap(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 4 == 0 && year % 100 != 0) {
        return true;
    }
    return false;
}

const int DAY[13] = {0, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int getMonth(int year, int month) {
    if (month != 2) {
        return DAY[month];
    }
    if (isLeap(year)) {
        return 29;
    }
    return 28;
}

bool isValid(int year, int month, int day) {
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > getMonth(year, month)) {
        return false;
    }
    return true;
}

int main() {
    while (scanf("%s", buffer) == 1) {
        int n = strlen(buffer);
        if (n == 10) {
            if (buffer[2] == buffer[5] && isSeperator(buffer[2])) {
                buffer[2] = buffer[5] = ' ';
                bool valid = true;
                for (int i = 0; i < 10; ++ i) {
                    if (i != 2 && i != 5) {
                        valid &= isdigit(buffer[i]);
                    }
                }
                if (valid) {
                    int y, m, d;
                    sscanf(buffer, "%d%d%d", &d, &m, &y);
                    if (isValid(y, m, d)) {
                        dates.push_back(Date(y, m, d));
                    }
                }
            }
        }
    }
    int n = dates.size();
    vector <Date> values;
    for (int i = 0; i < n; ++ i) {
        values.push_back(dates[i]);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int m = values.size();
    vector <int> id;
    for (int i = 0; i < n; ++ i) {
        id.push_back(lower_bound(values.begin(), values.end(), dates[i]) - values.begin() + 1);
    }
    vector <int> cnt(m + 1, 0);
    long long result = 0;
    for (int i = n - 1; i >= 0; -- i) {
        for (int k = id[i] - 1; k >= 1; k -= k & -k) {
            result += cnt[k];
        }
        for (int k = id[i]; k <= m; k += k & -k) {
            cnt[k] ++;
        }
    }
    cout << result << endl;
    return 0;
}
