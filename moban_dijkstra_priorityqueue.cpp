#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int N = 10005;
int n, m;
struct node {
	int v, w;
	node (int vi, int wi) {
		v = vi;
		w = wi;
	}
};
vector <node> g[N];
struct point {
	int id, d;
	point (int idi, int di) {
		id = idi;
		d = di;
	}
	bool operator < (const point x)const {
		return x.d < this-> d;
	}
};
priority_queue <point> q;
int dis[N];
bool inq[N];
void Dijstra () {
	memset (dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q.push(point(1, 0));
	while (!q.empty()) {
		int u = q.top().id;
		q.pop();
		if (inq[u]) {
			continue;
		}
		inq[u] = 1;
		for (unsigned i = 0; i < g[u].size(); i++) {
			int v = g[u][i].v;
			int w = g[u][i].w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push(point(v, dis[v]));
			}
		}
	}
}
int main() {
	scanf ("%d%d", &n, &m);
	int x, y, z;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d%d", &x, &y, &z);
		g[x].push_back(node(y, z));
	}
	Dijstra();
	printf ("%d\n", dis[n]);
	return 0;
}