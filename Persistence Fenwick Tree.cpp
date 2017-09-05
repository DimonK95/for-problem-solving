#include <stdio.h>
#include <iostream>
#include<iomanip>

#include<algorithm>

#include<string>
#include<vector>
#include<set>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define sz(a) int(a.size())
#define mp make_pair

typedef long long li;
typedef pair<pair<int, int>, int> pnt;
const int MOD = int(1e9) + 7;
const int MOD2 = 1000000009;
const int INF = 1e9;
const int N = int(2e5) + 7;
const int LEN = 250;
const int M = 350;
#define all(w) w.begin(), w.end()

int a[N], b[N];
vector <pair<int, int>>  f[N];
int n, m;
int re[N], last[N];

inline void upd(int version, int pos, int x) {
	for (int i = pos; i < n; i = (i | (i + 1))) {
		f[i].push_back(mp(version, f[i].back().second + x));
	}
}

int mi[N];
inline int answer(int pos, int k) {
	k--;
	int len = (1 << 17), l = 0;
	while (len != 0 && l < n) {
		int r = l + len - 1;
		if (r < n) {
			int idx = lower_bound(all(f[r]), mp(mi[pos], INF)) - f[r].begin() - 1;
			int val = f[r][idx].second;
			if (k >= val) {
				l = r + 1;
				k -= val;
			}
		}
		len >>= 1;
	}
	l--;
	if (k != 0 || l >= n - 1)
		return -1;
	return l + 1;
}
void solve() {

	scanf("%d %d", &n, &m);
	for (int i = 0; i < N; i++) {
		re[i] = -1;
		last[i] = -1;
		a[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
	}
	for (int i = 0; i < n; i++) {
		if (last[b[i]] == -1) {
			a[i] = 1;
		}
		else {
			re[last[b[i]]] = i;
		}
		last[b[i]] = i;
	}
	for (int i = 0; i < N; i++) {
		f[i].push_back(mp(0, 0));
	}
	int tek_version = 0;
	for (int i = 0; i < n; i++) {
		upd(++tek_version, i, a[i]);
	}
	mi[0] = tek_version;
	for (int i = 0; i < n; i++) {
		upd(++tek_version, i, -1);
		if (re[i] != -1) {
			upd(++tek_version, re[i], 1);
		}
		mi[i + 1] = tek_version;
	}

	int q;
	scanf("%d", &q);
	int p = 0;
	for (int j = 0; j < q; j++) {
		int x, y;
		scanf("%d %d", &x, &y);
		int l = ((x + p) % n);
		int k = ((y + p) % m + 1);
		p = answer(l, k) + 1;
		printf("%d\n", p);
	}
}


int main() {
	freopen("rollback.in", "r", stdin);
	freopen("rollback.out", "w", stdout);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	cout << setprecision(15) << fixed;

	solve();

	return 0;
}
