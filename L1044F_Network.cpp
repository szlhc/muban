#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 100005;
int n, m, deep, ans, tmp;
int dfn[N], low[N];
struct node {
	int cnt, v;
};
vector <node> g[N];
void Tarjan (int u, int fa) {
	deep++;
	dfn[u] = deep;
	low[u] = deep;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		if (!dfn[v]) {
			Tarjan (v, u);
			low[u] = min (low[u], low[v]);
			if (low[v] > dfn[u]) {
				if (g[u][i].cnt == 1) {
					ans++;
				}
			}
		} else {
			if (dfn[v] < dfn[u] && v != fa){
				low[u] = min (low[u], dfn[v]);
			}
		}
	}
}
void clean () {
	memset (dfn, 0, sizeof(dfn));
	memset (low, 0, sizeof(low));
	ans = 0;
	deep = 0;
}
int main() {
	while (1) {
		scanf ("%d%d", &n, &m);
		if (n == 0 && m == 0) {
			break;
		}
		int a, b;
		bool vis = 0;
		for (int i = 1; i <= m; i++) {
			scanf ("%d%d", &a, &b);
			vis = 0;
			for (unsigned j = 0; j < g[a].size(); j++) {
				if (g[a][j].v == b) {
					g[a][j].cnt++;
					vis = 1;
				}
			}
			if (vis) {
				for (unsigned j = 0; j < g[b].size(); j++) {
					if (g[b][j].v == a) {
						g[b][j].cnt++;
					}
				}
			}
			if (!vis) {
				g[a].push_back((node){1, b});
				g[b].push_back((node){1, a});
			}
		}
		tmp++;
		printf ("Case %d:\n", tmp);
		int q;
		scanf ("%d", &q);
		for (int i = 1; i <= q; i++) {
			scanf ("%d%d", &a, &b);
			vis = 0;
			for (unsigned j = 0; j < g[a].size(); j++) {
				if (g[a][j].v == b) {
					g[a][j].cnt++;
					vis = 1;
				}
			}
			if (vis) {
				for (unsigned j = 0; j < g[b].size(); j++) {
					if (g[b][j].v == a) {
						g[b][j].cnt++;
					}
				}
			}
			if (!vis) {
				g[a].push_back((node){1, b});
				g[b].push_back((node){1, a});
			}
			Tarjan (1, -1);
			printf ("%d\n", ans);
			clean ();
		}
		for (int i = 0; i <= n; i++) {
			g[i].clear();
		}
		printf ("\n");
	}
	return 0;
}
