#include <cstdio>
#include<iostream>
using namespace std;
const int N = 2005;
int S[N];
char c;
int x, y;
int n, m;
int getf(int x) {
    if (S[x] == x) {
    	return x;
	} 
    return S[x] = getf(S[x]);
}
void merge(int a, int b) {
    int u = getf(a);
	int v = getf(b);
    if (u != v) {
        S[u] = v;
    }
}
int main() {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= 2 * n + 1; i++) {
        S[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        scanf ("\n%c%d%d", &c, &x, &y);
        if (c == 'E') {
            merge(x + n, y);
            merge(y + n, x);
        } else {
            merge(x, y);
            merge(x + n, y + n);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (S[i] == i) {
        	ans++;
		} 
    }
    printf ("%d\n", ans);
    return 0;
}
