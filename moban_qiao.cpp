#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 5005;
int n, m, deep, ans;
int dfn[N], low[N];
vector <int> g[N];
struct edge {
	int u, v;
};
vector <edge> st;
void Tarjan (int u, int fa) {
	deep++;
	dfn[u] = deep;
	low[u] = deep;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!dfn[v]) {
			Tarjan (v, u);
			low[u] = min (low[u], low[v]);
			if (low[v] > dfn[u]) {
				st.push_back ((edge){u, v});
				ans++;
			}
		} else {
			if (dfn[v] < dfn[u] && v != fa){
				low[u] = min (low[u], dfn[v]);
			}
		}
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
	for (unsigned i = 0; i < st.size(); i++) {
		printf ("from: %d, to: %d\n", st[i].u, st[i].v);
	}
	printf ("%d\n", (ans + 1) / 2);
	return 0;
}
