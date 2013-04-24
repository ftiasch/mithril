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

const string ranks = "_A23456789_JQK";
const string suits = "CHDS";

struct Card
{
    int rank, suit;

    Card(const char *str) {
        if (str[0] == '1' && str[1] == '0') {
            rank = 10;
            str += 2;
        } else {
            rank = ranks.find(str[0]);
            str ++;
        }
        suit = suits.find(*str);
    }

    void print() {
        if (rank == 10) {
            printf("10");
        } else {
            putchar(ranks[rank]);
        }
        putchar(suits[suit]);
    }

    bool operator<(const Card &o) const {
        return rank < o.rank || rank == o.rank && suit < o.suit;
    }
};

struct Piles
{
    vector<Card> pile[4];

    void fromDeck(const vector<Card> &cards) {
        for (int i = 0; i < 4; i++) {
            pile[i].clear();
        }
        for (int it = 0; 4 * it < cards.size(); ++it) {
            bool allSame = true;
            for (int i = 1; i < 4; i++) {
                if (cards[it * 4 + i].rank != cards[it * 4 + i - 1].rank) {
                    allSame = false;
                    break;
                }
            }
            if (allSame) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                pile[i].push_back(cards[it * 4 + i]);
            }
            while (true) {
                bool found = false;
                for (int i = 3; i > 0; i--) {
                    if (pile[i].empty()) {
                        continue;
                    }
                    for (int j = 0; j < i; j++) {
                        if (!pile[j].empty() && pile[i].back().rank == pile[j].back().rank) {
                            pile[j].push_back(pile[i].back());
                            pile[i].pop_back();
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    break;
                }
            }
        }
    }

    vector<Card> toDeck() const {
        vector<Card> ret;
        for (int i = 0; i < 4; i++) {
            FOR (it, pile[i]) {
                ret.push_back(*it);
            }
        }
        return ret;
    }
};

set<vector<Card> > S;

int main()
{
    vector<Card> s;
    for (int i = 0; i < 52; i++) {
        string si;
        cin >> si;
        s.push_back(Card(si.c_str()));
    }
    reverse(s.begin(), s.end());
    S.insert(s);
    Piles piles;
    while (true) {
        for (int i = s.size() - 1; i >= 0; i--) {
            s[i].print();
            putchar(i == 0 ? '\n' : ' ');
        }
        piles.fromDeck(s);
        vector<Card> ns = piles.toDeck();
        if (ns.empty() || S.count(ns)) {
            break;
        }
        S.insert(ns);
        s = ns;
    }
}
