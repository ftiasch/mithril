#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

struct Point {
	int x, y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}

	bool on(const Point &, const Point &) const;
};

Point operator -(const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

int dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

int det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

bool Point::on(const Point &a, const Point &b) const {
	Point p = *this;
	return det(p - a, p - b) == 0 && dot(p - a, p - b) < 0;
}

const int N = 100;

int n;
Point points[N];

vector <int> valid_moves[N];

int below_left[N], below_right[N], below_point[N], below_segment[N][N];

bool visit_array[N][N + 1][N + 1];
int previous_array[N][N + 1][N + 1];

int min3(int a, int b, int c) {
	return min(a, min(b, c));
}

int max3(int a, int b, int c) {
	return max(a, max(b, c));
}

struct State {
	int now, line_count, below_count;

	State (int now, int line_count, int below_count) : now(now),
													 line_count(line_count),
													 below_count(below_count) { }

	bool &visit() { return visit_array[now][line_count][below_count]; }

	int &previous() { return previous_array[now][line_count][below_count]; }

	int evaluate() const {
		if (below_right[now] == -1) {
			return INT_MAX;
		}
		int a = line_count;
		int b = below_count + below_right[now];
		int c = n - a - b;
		return max3(a, b, c) - min3(a, b, c);
	}
};

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &points[i].x, &points[i].y);
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			if (points[i].x < points[j].x) {
				bool valid = true;
				for (int k = 0; k < n; ++ k) {
					if (i != k && j != k) {
						valid &= !points[k].on(points[i], points[j]);
					}
				}
				if (valid) {
					valid_moves[i].push_back(j);
				}
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		bool found = false;
		for (int j = 0; j < n; ++ j) {
			found |= points[j].y == points[i].y && points[j].x < points[i].x;
		}
		if (found) {
			below_left[i] = -1; 
		} else {
			below_left[i] = 0;
			for (int j = 0; j < n; ++ j) {
				below_left[i] += (points[j].x < points[i].x && points[j].y < points[i].y);
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		bool found = false;
		for (int j = 0; j < n; ++ j) {
			found |= points[j].y == points[i].y && points[j].x > points[i].x;
		}
		if (found) {
			below_right[i] = -1; 
		} else {
			below_right[i] = 0;
			for (int j = 0; j < n; ++ j) {
				below_right[i] += points[j].x > points[i].x && points[j].y < points[i].y;
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		below_point[i] = 0;
		for (int j = 0; j < n; ++ j) {
			below_point[i] += points[j].x == points[i].x && points[j].y < points[i].y;
		}
	}
	for (int i = 0; i < n; ++ i) {
		foreach (iter, valid_moves[i]) {
			int j = *iter;
			below_segment[i][j] = 0;
			for (int k = 0; k < n; ++ k) {
				below_segment[i][j] += points[i].x < points[k].x && points[k].x < points[j].x && det(points[k] - points[i], points[j] - points[i]) > 0;
			}
		}
	}
	queue <State> states;
	for (int i = 0; i < n; ++ i) {
		if (below_left[i] != -1) {
			State state(i, 1, below_left[i] + below_point[i]);
			state.visit() = true;
			state.previous() = -1;
			states.push(state);
		}
	}
	int answer = INT_MAX;
	State bestEnd(-1, -1, -1);
	while (!states.empty()) {
		State s = states.front();
		if (s.evaluate() < answer) {
			answer = s.evaluate();
			bestEnd = s;
		}
		states.pop();
		int u = s.now;
		foreach (iter, valid_moves[u]) {
			int v = *iter;
			State next(v, s.line_count + 1, s.below_count + below_segment[u][v] + below_point[v]);
			if (!next.visit()) {
				next.visit() = true;
				next.previous() = u;
				states.push(next);
			}
		}
	}
	vector <int> lines;
	State s = bestEnd;
	while (s.previous() != -1) {
		int v = s.now;
		lines.push_back(v);
		int u = s.previous();
		s = State(u, s.line_count - 1, s.below_count - below_point[v] - below_segment[u][v]);
	}
	lines.push_back(s.now);
	reverse(lines.begin(), lines.end());
	printf("%d\n", (int)lines.size());
	for (int i = 0; i < (int)lines.size(); ++ i) {
		printf("%d%c", lines[i] + 1, i == (int)lines.size() - 1 ? '\n' : ' ');
	}
	return 0;
}
