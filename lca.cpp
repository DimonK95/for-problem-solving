#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:640000000")

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <numeric>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
#include <bitset>

using namespace std;

#define forn(i, n) for(int i = 0; i < (int)(n); i++)
#define forn1(i, n) for(int i = 1; i <= (int)(n); i++)
#define forr(i, l, r) for(int i = int(l); i <= int(r); i++)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define sqr(x) ((x) * (x))

typedef long long li;
typedef pair<int, int> pnt;
const int INF = 1e9 + 7;
const int N = 2e5 + 5;
const int K = 30;
const li MOD = 1e9 + 7;
const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1 ,1 };
const double PI = acos(-1.0);

int pred[N][K];
int tin[N], tout[N];
vector<int> g[N];
int timer = 0;

bool is_accestor(int a, int b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void dfs(int v, int p) {
	tin[v] = timer++;
	pred[v][0] = p;
	for (int i = 1; i < K; i++) {
		pred[v][i] = pred[pred[v][i - 1]][i - 1];
	}
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == p) continue;
		dfs(to, v);
	}
	tout[v] = timer++;
}

int get_lca(int a, int b) {
	if (is_accestor(a, b))
		return a;
	if (is_accestor(b, a))
		return b;

	int v = a;
	for (int i = K - 1; i >= 0; i--) {
		if (is_accestor(pred[a][i], b)) continue;
		a = pred[a][i];
	}
	return pred[a][0];
}

void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(0, 0);
	int a, b;
	while (cin >> a >> b) {
		a--; b--;
		cout << get_lca(a, b) + 1 << ' ';
	}

}

int main() {
	
#if _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cout.sync_with_stdio(false);
	cin.tie(0);
	srand(time(NULL));
	solve();
	return 0;
}
