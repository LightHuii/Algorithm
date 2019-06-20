#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 1000
int dp[MAX] = { 0, };
int ary[MAX];
int N;

//dp[i]: i가 포함된 부분 증가 수열 중 가장 긴 길이

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> ary[i];

	int rst = 1;		//부분 수열들의 길이 중 가장 긴 값
	dp[0] = 1;

	for (int i = 1; i < N; i++) {
		int idx = i - 1;

		//현재보다 작고, dp가 가장 큰 좌표를 0 ~ i-1에서 찾는다
		int tmp = 0;
		for (int j = 0; j < i; j++) {
			if (ary[j] < ary[i])
				tmp = max(tmp, dp[j]);
		}

		dp[i] = tmp + 1;
		rst = max(dp[i], rst);
	}
	cout << rst << endl;

	return 0;
}