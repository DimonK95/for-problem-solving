#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<string>
#include<map>
#include<unordered_map>
#include<stdio.h>
#include<stack>
#include<queue>
#include<assert.h>
#include<time.h>
#include <math.h>
using namespace std;
const int N = 1e3 + 2;
vector<pair<int, int>> g[N];
bool used[N];
int fup[N];
int tin[N];
vector<int> point;
int T;

void dfs(int v, int p = -1){
	fup[v] = tin[v] = T++;
	used[v] = true;
	int cnt = 0;
	bool was = false;

	for (int i = 0; i < g[v].size(); i++){
		int to = g[v][i].first;
		if (p == to) continue;
		if (used[to]){
			fup[v] = min(fup[v], tin[to]);
		}
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (!was && p != -1 && tin[v] <= fup[to]){
				point.push_back(v);
				was = true;
			}
			cnt++;
		}
	}

	if (p == -1 && cnt > 1){
		point.push_back(v);
	}
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		g[a].push_back(make_pair(b, i));
		g[b].push_back(make_pair(a, i));
	}

	for (int i = 0; i < n; i++){
		if (!used[i]){
			dfs(i);
		}
	}
	sort(point.begin(), point.end());
	printf("%d\n", point.size());
	for (int i = 0; i < point.size(); i++)
		printf("%d ", point[i] + 1);
	return 0;
}
