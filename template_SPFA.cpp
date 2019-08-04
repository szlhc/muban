#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int N = 10005;
int n, m;
struct node {
	int v, w;
};
vector <node> g[N];
queue <int> q;
int num[N], inq[N], d[N];
bool spfa () {
	memset (d, 0x3f, sizeof(d));
	d[1] = 0;
	q.push(1);
	num[1]++;
	inq[1] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		for (unsigned i = 0; i < g[u].size(); i++) {
			int v = g[u][i].v;
			int w = g[u][i].w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				if (!inq[v]) {
					q.push(v);
					num[v]++;
					if (num[v] >= n) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
int main() {
	scanf ("%d%d", &n, &m);
	int x, y, z;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d%d", &x, &y, &z);
		g[x].push_back((node){y, z});
	}
	bool tmp = spfa();
	if (tmp) {
		printf ("%d\n", d[n]);
	} else {
		printf ("Impossible!\n");
	}
	return 0;
}
