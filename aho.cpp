#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <queue>
#include <string.h>
#include <string>
#include <algorithm>
#include <assert.h>
using namespace std;
#define mp make_pair

typedef long long li;
int go(int v, int c);
int link(int v);

const int N = 2e4 + 5;
const int K = 26;
int goo[N][K];
int slink[N];
int pch[N];
int to[N][K];
li ok[N];
int numV;
int p[N];
li term[N];

void init() {
	memset(goo, -1, sizeof goo);
	memset(slink, -1, sizeof slink);
	memset(to, -1, sizeof to);
	memset(pch, -1, sizeof pch);
	memset(p, -1, sizeof p);
	memset(ok, -1, sizeof ok);
	numV = 1;
}
#define sz(x) (int)x.size()

int go(int v, int c) {
	if (goo[v][c] != -1)
		return goo[v][c];

	if (to[v][c] != -1) {
		return goo[v][c] = to[v][c];
	}

	if (v == 0) {
		return goo[v][c] = 0;
	}
	return goo[v][c] = go(link(v), c);
}

int link(int v) {
	if (slink[v] != -1)
		return slink[v];


	if (v == 0 || p[v] == 0) {
		return slink[v] = 0;
	}

	return slink[v] = go(link(p[v]), pch[v]);
}

void add(string s, int cr) {
	int v = 0;
	for (int i = 0; i < sz(s); i++) {
		if (to[v][s[i] - 'a'] == -1) {
			to[v][s[i] - 'a'] = numV;
			pch[numV] = s[i] - 'a';
			p[numV] = v;
			numV++;
		}
		v = to[v][s[i] - 'a'];
	}
	term[v] = cr;
}

li okay(int v) {
	if (ok[v] != -1) {
		return ok[v];
	}
	if (v == 0) {
		return 0;
	}
	ok[v] = (term[v] + (okay(link(v))));
	return ok[v];
}
const int L = 1e6 + 56;
char c[L];
int m;

const int M = 102;
li dp[N][M];
li calc(int v, int len) {
	if (dp[v][len] != -1LL)
		return dp[v][len];
	if (len >= m) {
		return dp[v][len] = okay(v);
	}
	li ans = 0;;
	for (int i = 0; i < K; i++) {
		ans = max(ans, calc(go(v, i), len + 1));
	}
	ans += okay(v);
	return dp[v][len] = ans;
}
string ans;
void restore(int v, int len) {
	if (len >= m) {
		return;
	}
	for (int i = 0; i < K; i++) {
		if (okay(v) + calc(go(v, i), len + 1) == calc(v, len)) {
			ans += char('a' + i);
			restore(go(v, i), len + 1);
			return;
		}
	}
	throw logic_error("E");
}
int main() {
#if _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n;
	init();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", &c);
		string s = string(c);
		int x;
		scanf(" %d", &x);
		::add(s, x);
	}
	scanf("%d", &m);
	for (int i = 0; i < N; i++)
		for (int k = 0; k < M; k++)
			dp[i][k] = -1;
	cout << calc(0, 0) << endl;
	restore(0, 0);
	cout << ans;

}
