//如有错误，先检查初始化
#include <cstdio>
using namespace std;
const int N = 10005;//根据题意写
int n, m, q;//n个点，m条边, q个问题
int S[N];
int getf (int x) {//找到它的父亲
	if (x == S[x]) {
		return x;//边界
	}
	return S[x] = getf(S[x]);//路径压缩
}
void merge (int x, int y) {//合并
	int a = getf(x);
	int b = getf(y);
	if (a != b) {
		S[a] = b;
		S[x] = b;//路径压缩
	}
}
int main() {
	scanf ("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) {
		S[i] = i;//初始化，每个节点的父亲是自己
	}
	int x, y;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d", &x, &y);
		merge(x, y);
	}
	for (int i = 1; i <= q; i++) {
		scanf ("%d%d", &x, &y);
		if (getf(x) == getf(y)) {
			printf("Yes\n");
		} else {
			printf ("No\n");
		}
	}
	return 0;
}