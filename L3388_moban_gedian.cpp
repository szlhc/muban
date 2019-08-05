#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 20005;
int n, m, deep, ans;
int dfn[N], low[N];
bool iscut[N];
vector <int> g[N];
void Tarjan (int u, int fa) {
	int child = 0;
	deep++;
	low[u] = deep;
	dfn[u] = deep;
	for (unsigned i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!dfn[v]) {
			child++;
			Tarjan (v, u);
			low[u] = min (low[u], low[v]);
			if (low[v] >= dfn[u]) {//?
				iscut[u] = 1;
			}
		} else {
			if (v != fa && dfn[v] < dfn[u]) {//?
				low[u] = min (low[u], dfn[v]);
			}
		}
	}
	if (fa < 0 && child == 1) {
		iscut[u] = 0;
	}
}
int main() {
	scanf ("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			Tarjan (i, -1);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (iscut[i]) {
			ans++;	
		}
	}
	printf ("%d\n", ans);
	for (int i = 1; i <= n; i++) {
		if (iscut[i]) {
			printf ("%d ", i);
		}
	}
	return 0;
}
