#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

bool is_leap(int year) {
    if (year % 100 == 0) {
        return year % 400 == 0;
    }
    return year % 4 == 0;
}

const int MONTH_DAY[13] = {-1, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get_day(int year, int month) {
    if (month == 2) {
        return is_leap(year) ? 29 : 28;
    }
    return MONTH_DAY[month];
}

struct Date {
    int year, month, day;

    Date(int year = 0, int month = 0, int day = 0) : year(year), month(month), day(day) {}

    Date(char* str) {
        sscanf(str + 6, "%d", &day);
        str[6] = '\0';
        sscanf(str + 4, "%d", &month);
        str[4] = '\0';
        sscanf(str, "%d", &year);
    }

    Date succ() {
        Date ret(*this);
        ret.day ++;
        if (ret.day > get_day(ret.year, ret.month)) {
            ret.day = 1;
            ret.month ++;
        }
        if (ret.month > 12) {
            ret.month = 1;
            ret.year ++;
        }
        return ret;
    }

    Date pred() {
        Date ret(*this);
        if (ret.month == 1 && ret.day == 1) {
            ret.year --;
            ret.month = 12;
            ret.day = get_day(ret.year, ret.month);
        } else {
            ret.day --;
            if (ret.day < 1) {
                ret.month --;
                ret.day = get_day(ret.year, ret.month);
            }
        }
        return ret;
    }

    void print() {
        printf("%d/%d/%d", month, day, year);
    }
};

bool operator < (const Date &a, const Date &b) {
    if (a.year != b.year) {
        return a.year < b.year;
    }
    if (a.month != b.month) {
        return a.month < b.month;
    }
    return a.day < b.day;
}

bool operator == (const Date &a, const Date &b) {
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

Date read_date() {
    char buffer[9];
    scanf("%s", buffer);
    return Date(buffer);
}

const int N = 100;

Date dates[2][N][2];

int main() {
    int test_count = 0;
    int count[2];
    while (scanf("%d%d", count, count + 1) == 2 && count[0] + count[1]) {
        std::vector <Date> values;
        for (int t = 0; t < 2; ++ t) {
            for (int i = 0; i < count[t]; ++ i) {
                for (int x = 0; x < 2; ++ x) {
                    dates[t][i][x] = read_date();
                    values.push_back(dates[t][i][x]);
                }
                values.push_back(dates[t][i][0].pred());
                values.push_back(dates[t][i][1].succ());
            }
        }
        std::sort(values.begin(), values.end());
        values.erase(std::unique(values.begin(), values.end()), values.end());
        int s = values.size();
        std::vector <int> flag(s, 0);
#define GET_ID(v) (std::lower_bound(values.begin(), values.end(), (v)) - values.begin())
        for (int t = 0; t < 2; ++ t) {
            for (int i = 0; i < count[t]; ++ i) {
                int from = GET_ID(dates[t][i][0]);
                int to = GET_ID(dates[t][i][1]);
                for (int j = from; j <= to; ++ j) {
                    flag[j] |= 1 << t;
                }
            }
        }
#undef GET_ID
        if (test_count > 0) {
            puts("");
        }
        printf("Case %d:\n", ++ test_count);
        bool found = false;
        for (int i = 0; i < s; ++ i) {
            if (flag[i] != 2) {
                continue;
            }
            found = true;
            int j = i;
            while (j < s && flag[j] == 2) {
                j ++;
            }
            if (i == j - 1) {
                values[i].print();
            } else {
                values[i].print();
                printf(" to ");
                values[j - 1].print();
            }
            puts("");
            i = j - 1;
        }
        if (!found) {
            puts("No additional quotes are required.");
        }
    }
    return 0;
}
