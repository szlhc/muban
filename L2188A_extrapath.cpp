#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1005;
int n, m, deep, ans;
int dfn[N], low[N], tmp1[N][N], root;
struct node {
	bool flag;
	int v;
};
vector <node> g[N];
vector <int> g1[N];
void Tarjan (int u, int fa) {
	deep++;
	dfn[u] = deep;
	low[u] = deep;
	for (unsigned i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		if (!dfn[v]) {
			Tarjan (v, u);
			low[u] = min (low[u], low[v]);
			if (low[v] > dfn[u]) {
				g[u][i].flag = 1;
				for (unsigned j = 0; j < g[v].size(); j++) {
					if (g[v][j].v == u) {
						g[v][j].flag = 1;
					}
				}
			}
		} else {
			if (dfn[v] < dfn[u] && v != fa){
				low[u] = min (low[u], dfn[v]);
			}
		}
	}
}
int vis[N], color[N], du[N], tmp[N];
void dfs (int u) {
	if (vis[u]) {
		return;
	}
	vis[u] = 1;
	color[u] = root;
	for (unsigned i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		if (!g[u][i].flag) {
			color[v] = root;
			dfs(v);
		}
	}
}
int main() {
	scanf ("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d", &a, &b);
		if (!tmp1[a][b]) {
			tmp1[a][b] = 1;
			tmp1[b][a] = 1;
			g[a].push_back((node){0, b});
			g[b].push_back((node){0, a});
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			Tarjan (i, -1);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			root = i;
			dfs(i);
		}
	}
	/*
	for (int i = 1; i <= n; i++) {
		printf ("color: %d: %d\n", i, color[i]);
	}
	*/
	for (int i = 1; i <= n; i++) {
		for (unsigned j = 0; j < g[i].size(); j++) {
			int v = g[i][j].v;
			if (color[i] != color[v]) {
				g1[color[i]].push_back(color[v]);
				g1[color[v]].push_back(color[i]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		memset (tmp, 0, sizeof(tmp));
		for (unsigned j = 0; j < g1[i].size(); j++) {
			if (g1[i].empty()) {
				continue;
			}
			int v = g1[i][j];
			if (!tmp[v]) {
				tmp[v] = 1;
				du[i]++;
				//printf ("from: %d, to: %d\n", i, v);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (du[i] == 1) {
			ans++;
			//printf ("leaf: %d\n", i);
		}
	}
	if (ans == 0) {
		printf ("0\n");
		return 0;
	}
	printf ("%d\n", (ans + 1) / 2);
	return 0;
}
