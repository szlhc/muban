#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
const int N = 2005;
int n, m, deep, ans;
int dfn[N], low[N], color[N], du[N], tmp[N];
vector <int> g[N];
vector <int> g1[N];
stack <int> s;
void Tarjan (int u, int fa) {
	deep++;
	dfn[u] = deep;
	low[u] = deep;
	s.push(u);
	for (unsigned i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!dfn[v]) {
			Tarjan (v, u);
			low[u] = min (low[u], low[v]);
		} else {
			if (dfn[v] < dfn[u] && v != fa){
				low[u] = min (low[u], dfn[v]);
			}
		}
	}
	if (low[u] == dfn[u]) {
		color[u] = u;
		while (s.top() != u) {
			color[s.top()] = u;
			s.pop();
		}
		s.pop();
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
	Tarjan (1, -1);
	for (int i = 1; i <= n; i++) {
		for (unsigned j = 0; j < g[i].size(); j++) {
			int v = g[i][j];
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
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (du[i] == 1) {
			ans++;
		}
	}
	printf ("%d\n", (ans + 1) / 2);
	return 0;
}
