//最重要的是转换思想，即从字符串变成数
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 10005;//根据题意写
const int p = 1000007;//乘一个大质数以避免冲突
int n;
vector <int> a;
string s;
long long Hash (string str) {
	long long h = 0;
	for (unsigned i = 0; i < str.length(); i++) {
		h = p * h + s[i];//求出Hash值
	}
	return h;
}
int main (){
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) {
		cin >> s;
		int id = Hash(s);
		a.push_back(id);
	}
	sort (a.begin(), a.end());
	int cnt = 0;
	for (unsigned i = 0; i < a.size(); i++) {
		if (i == 0 || a[i - 1] != a[i]) {
			cnt++;
		}
	}
	printf ("%d\n", cnt);
	return 0;
}