#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define FOR(i,a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)

long long gcd(long long a, long long b)
{
	while (b != 0) {
		long long r = a % b;
		a = b;
		b = r;
	}
	return a;
}

struct Rational
{
	long long p, q;

	Rational(long long p = 0, long long q = 1) : p(p), q(q) {
		normalize();
	}

	Rational &normalize() {
		assert(q != 0);
		if (q < 0) {
			p = -p;
			q = -q;
		}
		long long g = gcd(abs(p), q);
		p /= g;
		q /= g;
		return *this;
	}

	Rational operator+(const Rational &o) const {
		return Rational(p * o.q + q * o.p, q * o.q);
	}

	Rational operator-(const Rational &o) const {
		return Rational(p * o.q - q * o.p, q * o.q);
	}

	Rational operator*(const Rational &o) const {
		return Rational(p * o.p, q * o.q);
	}

	Rational operator/(const Rational &o) const {
		return Rational(p * o.q, q * o.p);
	}
};

Rational &operator+=(Rational &a, const Rational &b)
{
	return a = a + b;
}

Rational &operator-=(Rational &a, const Rational &b)
{
	return a = a - b;
}

Rational &operator*=(Rational &a, const Rational &b)
{
	return a = a * b;
}

Rational &operator/=(Rational &a, const Rational &b)
{
	return a = a / b;
}

typedef pair<long long, Rational> X;
typedef map<long long, Rational> XStar;

X &normalize(X &x)
{
	for (long long i = 2; i * i <= x.first; i ++) {
		while (x.first % (i * i) == 0) {
			x.first /= i * i;
			x.second *= i;
		}
	}
	return x;
}

XStar &normalize(XStar &m)
{
	XStar::iterator it = m.begin();
	while (it != m.end()) {
		XStar::iterator jt = it;
		++jt;
		if (it->second.p == 0) {
			m.erase(it);
		}
		it = jt;
	}
	return m;
}

X singleton(long long x)
{
	return X(1, x);
}

XStar singleton(const X &x)
{
	XStar ret;
	ret[x.first] = x.second;
	return normalize(ret);
}

XStar operator+(const XStar &a, const XStar &b)
{
	XStar r = a;
	FOR (it, b) {
		r[it->first] += it->second;
	}
	return normalize(r);
}

XStar operator-(const XStar &a, const XStar &b)
{
	XStar r = a;
	FOR (it, b) {
		r[it->first] -= it->second;
	}
	return normalize(r);
}

X operator*(const X &a, const X &b)
{
	X ret(a.first * b.first, a.second * b.second);
	long long g = gcd(a.first, b.first);
	ret.first /= g * g;
	ret.second *= g;
	return ret;
}

XStar operator*(const XStar &a, const XStar &b)
{
	XStar ret;
	FOR (it, a) {
		FOR (jt, b) {
			X ab = *it * *jt;
			ret[ab.first] += ab.second;
		}
	}
	return normalize(ret);
}

X operator/(const X &a, const X &b)
{
	X ret(a.first * b.first, a.second / b.second / b.first);
	long long g = gcd(a.first, b.first);
	ret.first /= g * g;
	ret.second *= g;
	return ret;
}

XStar operator/(const XStar &a, const XStar &b)
{
	assert(b.size() == 1);
	XStar ret;
	FOR (it, a) {
		FOR (jt, b) {
			X ab = *it / *jt;
			ret[ab.first] += ab.second;
		}
	}
	return normalize(ret);
}

XStar sqrt(const XStar &a)
{
	if (a.empty()) {
		return a;
	}
	assert(a.size() == 1);
	X x = *a.begin();
	assert(x.first == 1);
	X x2(x.second.p * x.second.q, Rational(1, x.second.q));
	return singleton(normalize(x2));
}

ostream &operator<<(ostream &out, const Rational &x)
{
	if (x.q == 1) {
		out << x.p;
	} else {
		out << x.p << "/" << x.q;
	}
	return out;
}

ostream &operator<<(ostream &out, const X &x)
{
	if (x.first == 1) {
		out << x.second;
	} else {
		if (x.second.q == 1 && abs(x.second.p) == 1) {
			if (x.second.p < 0) {
				out << '-';
			}
		} else {
			out << x.second << "*";
		}
		out << "sqrt(" << x.first << ")";
	}
}

ostream &operator<<(ostream &out, const XStar &a)
{
	bool first = true;
	FOR (it, a) {
		if (first) {
			first = false;
		} else {
			out << " + ";
		}
		out << *it;
	}
	if (first) {
		out << "0";
	}
	return out;
}

int main()
{
	string cmd;
	vector<XStar> st;
	while (cin >> cmd) {
		if (cmd == "push") {
			long long x;
			cin >> x;
			st.push_back(singleton(singleton(x)));
		} else if (cmd == "add" || cmd == "sub" || cmd == "mul" || cmd == "div") {
			assert(st.size() >= 2);
			XStar r2 = st.back();
			st.pop_back();
			XStar r1 = st.back();
			st.pop_back();
			if (cmd == "add") {
				st.push_back(r1 + r2);
			} else if (cmd == "sub") {
				st.push_back(r1 - r2);
			} else if (cmd == "mul") {
				st.push_back(r1 * r2);
			} else {
				st.push_back(r1 / r2);
			}
		} else if (cmd == "sqrt") {
			assert(st.size() > 0);
			st.back() = sqrt(st.back());
		} else if (cmd == "disp") {
			assert(st.size() > 0);
			cout << st.back() << endl;
			st.pop_back();
		} else if (cmd == "stop") {
			break;
		} else {
			assert(false);
		}
	}
}
