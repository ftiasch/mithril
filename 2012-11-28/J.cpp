#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y)
{
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long ret = extgcd(b, a % b, y, x);
	y -= a / b * x;
	return ret;
}

int main()
{
	long long a, da, b, db;
	while (cin >> a >> da >> db >> b && (a || da || db || b)) {
		b += db;
		if (da == 0 && db == 0) {
			if (a == b) {
				cout << a << endl;
			} else {
				cout << "Impossible" << endl;
			}
			continue;
		}
		if (da == 0) {
			if (a >= b && (a - b) % db == 0) {
				cout << a << endl;
			} else {
				cout << "Impossible" << endl;
			}
			continue;
		}
		if (db == 0) {
			if (b >= a && (b - a) % da == 0) {
				cout << b << endl;
			} else {
				cout << "Impossible" << endl;
			}
			continue;
		}
		long long x, y;
		long long g = extgcd(da, db, x, y);
		if ((b - a) % g != 0) {
			cout << "Impossible" << endl;
		} else {
			long long scale = (b - a) / g;
			x *= scale;
			y *= scale;
			y = -y;
			x %= db / g;
			y %= da / g;
			//assert(a + da * x == b + db * y);
			long long firstTime = a + da * x;
			long long deltaTime = da / g * db;
			if (firstTime < a) {
				firstTime += (a - firstTime) / deltaTime * deltaTime;
			}
			if (firstTime < b) {
				firstTime += (b - firstTime) / deltaTime * deltaTime;
			}
			while (firstTime < a || firstTime < b) {
				firstTime += deltaTime;
			}
			long long ab = max(a, b);
			if (firstTime > ab) {
				firstTime = (firstTime - ab) % deltaTime + ab;
			}
			cout << firstTime << endl;
		}
	}
}
