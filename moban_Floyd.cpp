#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 205;
int n;
double d[N][N];
struct node {
	int x, y;
}g[N];
double dis(int x, int y) {
    return sqrt((double)(g[x].x - g[y].x) * (g[x].x - g[y].x) + (double)(g[x].y - g[y].y) * (g[x].y - g[y].y));
}
int main() {
	int index = 0;
	while (1) {
		cin >> n;
		if (n == 0) {
			break;
		}
		index++;
		memset(d, 0, sizeof(d));
		for (int i = 1; i <= n; i++) {
			cin >> g[i].x >> g[i].y;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i != j) {
					d[i][j] = dis(i, j);
					d[j][i] = dis(i, j);
				}
			}
		}
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if(i != j && j != k && i != k) {
						if (d[i][j] > d[i][k] && d[i][j] > d[k][j]) {
							d[i][j] = max (d[i][k], d[k][j]);
							d[j][i] = max (d[i][k], d[k][j]);
						}
					}
				}
			}
		}
		printf ("Scenario #%d\n", index);
		printf ("Frog Distance = %.3lf\n\n", d[1][2]);
	}
	return 0;
}