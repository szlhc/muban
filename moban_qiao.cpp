#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 5005;
int n, m, deep, ans = 1000005;
int dfn[N], low[N];
struct node {
	int v, w;
};
vector <node> g[N];
void Tarjan (int u, int fa) {
	deep++;
	dfn[u] = deep;
	low[u] = deep;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		int w = g[u][i].w;
		if (!dfn[v]) {
			Tarjan (v, u);
			low[u] = min (low[u], low[v]);
			if (low[v] > dfn[u]) {
				ans = min (ans, w);
			}
		} else {
			if (dfn[v] < dfn[u] && v != fa){
				low[u] = min (low[u], dfn[v]);
			}
		}
	}
}
void clean () {
	for (int i = 0; i < n + 5; i++) {
		g[i].clear();
	}
	memset (dfn, 0, sizeof(dfn));
	memset (low, 0, sizeof(low));
	ans = 1000005;
	deep = 0;
}
int main() {
	while (cin >> n >> m) {
		clean();
		if (n == 0 && m == 0) {
			break;
		}
		int a, b, c;
		int maxw = 0;
		for (int i = 1; i <= m; i++) {
			scanf ("%d%d%d", &a, &b, &c);
			maxw = max (maxw, c);
			g[a].push_back((node){b, c});
			g[b].push_back((node){a, c});
		}
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) {
				Tarjan (i, -1);
			}
		}
		if (ans > maxw || ans == 1000005) {
			printf ("-1\n");
		} else {
			printf ("%d\n", ans);	
		}	
	}
	return 0;
}
