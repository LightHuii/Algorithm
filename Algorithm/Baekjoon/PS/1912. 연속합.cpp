#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 100000
int n;
int dp[MAX];
int ary[MAX];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ary[i];
		dp[i] = INT32_MIN;
	}

	int rst = INT32_MIN;
	dp[0] = ary[0];

	for (int i = 1; i < n; i++) {
		dp[i] = max(ary[i], dp[i - 1] + ary[i]);
		rst = max(rst, dp[i]);
	}

	rst = max(rst, ary[0]);
	cout << rst << endl;

	return 0;
}