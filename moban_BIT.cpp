#include <cstdio>
using namespace std;
const int N = 500005;
int n, m;
int b[N];
int lowbit (int x) {
	return x & -x;
}
//²éÑ¯ 
int query (int x) {
	int tmp = 0;
	for (; x > 0; x -= lowbit(x)) {
		tmp += b[x];
	}
	return tmp;
}
void update (int x, int v) {
	for (; x <= n; x += lowbit(x)) {
		b[x] += v;
	}
}
int main() {
	scanf ("%d%d", &n, &m);
	int v;
	for (int i = 1; i <= n; i++) {
		scanf ("%d", &v);
		update (i, v);
	}
	int a, b, c;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d%d", &a, &b, &c);
		if (a == 1) {
			update (b, c);
		} else {
			printf ("%d\n", query(c) - query(b - 1));
		}
	}
	return 0;
}
