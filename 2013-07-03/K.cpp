#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

const int PRE = 0;
const int IN = 1;
const int POST = 2;
const string MAGIC[3] = {
	"Pre", "In", "Post"
};

const int LEFT = 0;
const int RIGHT = 1;

const string unknown = "unknown";

int callTable[3][2];

struct Result
{
	string preOrder, inOrder, postOrder;
	bool valid;

	Result(bool flag = false) : valid(flag) {
	}

	Result(const string &a, const string &b, const string &c) : valid(true), preOrder(a), inOrder(b), postOrder(c) {}

	Result(char ch) : valid(true), preOrder(1, ch), inOrder(1, ch), postOrder(1, ch) {}

	bool operator<(const Result &o) const {
		return preOrder < o.preOrder || preOrder == o.preOrder && inOrder < o.inOrder;
	}

};
Result make(const Result &l, char root, const Result &r) {
	if (!l.valid || !r.valid) {
		return Result(false);
	}
	return Result(root + l.preOrder + r.preOrder,
			l.inOrder + root + r.inOrder,
			l.postOrder + r.postOrder + root);
}

int getMask(const string &s)
{
	int res = 0;
	for (int i = 0; i < s.size(); i++) {
		res |= 1 << s[i] - 'A';
	}
	return res;
}

Result solve(const string &a, const string &b, const string &c);

Result solve(const vector<pair<int, string> > &inputs)
{
	string first[3];
	bool vis[3];
	vis[0] = vis[1] = vis[2] = 0;
	for (int i = 0; i < inputs.size(); i++) {
		if (!vis[inputs[i].first]) {
			vis[inputs[i].first] = true;
			first[inputs[i].first] = inputs[i].second;
		} else if (first[inputs[i].first] != inputs[i].second) {
			return Result(false);
		}
	}
	return solve(vis[0] ? first[0] : "", vis[1] ? first[1] : "", vis[2] ? first[2] : "");
}

map<string,Result> memoA, memoB, memoC;

Result solve(const string &a, const string &b, const string &c)
{
	int n = max(a.size(), max(b.size(), c.size()));
	vector<pair<int,string> > inputs;
#define ADD(A,B,C) inputs.push_back(make_pair(callTable[A][B], C))
	if (a.size() && b.size() == 0 && c.size() == 0) {
		if (memoA.count(a)) {
			return memoA[a];
		}
		Result ret(false);
		int root = a[0];
		for (int i = 0; i < n; i++) {
			inputs.clear();
			ADD(PRE, LEFT, a.substr(1, i));
			Result lhs = solve(inputs);
			if (lhs.valid) {
				inputs.clear();
				ADD(PRE, RIGHT, a.substr(1 + i));
				Result res = make(lhs, root, solve(inputs));
				if (res.valid && (!ret.valid || res < ret)) {
					ret = res;
				}
			}
		}
		return memoA[a] = ret;
	}
	if (a.size() == 0 && b.size() == 0 && c.size()) {
		if (memoC.count(c)) {
			return memoC[c];
		}
		Result ret(false);
		char root = c[n - 1];
		for (int i = 0; i < n; i++) {
			inputs.clear();
			ADD(POST, LEFT, c.substr(0, i));
			Result lhs = solve(inputs);
			if (lhs.valid) {
				inputs.clear();
				ADD(POST, RIGHT, c.substr(i, n - 1 - i));
				Result res = make(lhs, root, solve(inputs));
				if (res.valid && (!ret.valid || res < ret)) {
					ret = res;
				}
			}
		}
		return memoC[c] = ret;
	}
	if (a.size() == 0 && b.size() && c.size() == 0) {
		if (memoB.count(b)) {
			return memoB[b];
		}
		Result ret(false);
		for (int i = 0; i < n; i++) {
			char root = b[i];
			inputs.clear();
			ADD(IN, LEFT, b.substr(0, i));
			Result lhs = solve(inputs);
			if (lhs.valid) {
				inputs.clear();
				ADD(IN, RIGHT, b.substr(i + 1));
				Result res = make(lhs, root, solve(inputs));
				if (res.valid && (!ret.valid || res < ret)) {
					ret = res;
				}
			}
		}
		return memoB[b] = ret;
	}
	if (true) {
		int maskA = getMask(a), maskB = getMask(b), maskC = getMask(c);
		int mask = max(maskA, max(maskB, maskC));
		if (maskA != 0 && maskA != mask || maskB != 0 && maskB != mask || maskC != 0 && maskC != mask) {
			return Result(false);
		}
	}
	if (n == 0) {
		return Result(true);
	}
	if (n == 1) {
		return Result((a + b + c)[0]);
	}
	if (b.size() == 0) {
		Result ret(false);
		// only pre and post
		if (a[0] == c[n - 1]) {
			char root = a[0];
			for (int i = 0; i < n; i++) {
				inputs.clear();
				ADD(PRE, LEFT, a.substr(1, i));
				ADD(POST, LEFT, c.substr(0, i));
				Result lhs = solve(inputs);
				if (lhs.valid) {
					inputs.clear();
					ADD(PRE, RIGHT, a.substr(1 + i));
					ADD(POST, RIGHT, c.substr(i, n - 1 - i));
					Result res = make(lhs, root, solve(inputs));
					if (res.valid && (!ret.valid || res < ret)) {
						ret = res;
					}
				}
			}
		}
		return ret;
	} else {
		char root = a.size() ? a[0] : c[n - 1];
		int pos = b.find(root);
		if (pos < 0) {
			return Result(false);
		}
		inputs.clear();
		if (a.size()) {
			ADD(PRE, LEFT, a.substr(1, pos));
		}
		ADD(IN, LEFT, b.substr(0, pos));
		if (c.size()) {
			ADD(POST, LEFT, c.substr(0, pos));
		}
		Result lhs = solve(inputs);
		if (lhs.valid) {
			inputs.clear();
			if (a.size()) {
				ADD(PRE, RIGHT, a.substr(pos + 1, n - 1 - pos));
			}
			ADD(IN, RIGHT, b.substr(pos + 1));
			if (c.size()) {
				ADD(POST, RIGHT, c.substr(pos, n - 1 - pos));
			}
			return make(lhs, root, solve(inputs));
		}
		return Result(false);
	}
}

int main()
{
	string a, b, c;
	while (cin >> a >> b >> c) {
		int perm[6];
		for (int i = 0; i < 6; i++) {
			perm[i] = i / 2;
		}
		bool first = true;
		do {
			for (int i = 0; i < 6; i++) {
				callTable[i / 2][i % 2] = perm[i];
			}
			memoA.clear();
			memoB.clear();
			memoC.clear();
			Result res = solve(a, b, c);
			if (res.valid) {
				if (first) {
					first = false;
				} else {
					cout << endl;
				}
				for (int i = 0; i < 6; i++) {
					if (i > 0) {
						cout << " ";
					}
					cout << MAGIC[perm[i]];
				}
				cout << endl;
				cout << res.preOrder << endl;
				cout << res.inOrder << endl;
				cout << res.postOrder << endl;
			}
		} while (next_permutation(perm, perm + 6));
	}
}
