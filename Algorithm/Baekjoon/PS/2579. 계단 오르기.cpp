#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 301
int dp[MAX][3];		//최대 점수, 현재까지 연속해서 오른 횟수
int N;
int stairs[MAX];

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> stairs[i];
		dp[i][0] = 0;
		dp[i][1] = 0;
	}
	dp[0][0] = 0;
	dp[0][1] = 0;
	dp[0][2] = 0;

	for (int i = 0; i < N; i++) {
		if (i + 1 < MAX) {
			if (dp[i + 1][1] < dp[i][0] + stairs[i + 1])
				dp[i + 1][1] = dp[i][0] + stairs[i + 1];
			if (dp[i + 1][2] < dp[i][1] + stairs[i + 1])
				dp[i + 1][2] = dp[i][1] + stairs[i + 1];
		}

		//2개를 이동할 경우 1번 이동한 것이 된다
		if (i + 2 < MAX) {
			if (dp[i + 2][1] < dp[i][0] + stairs[i + 2])
				dp[i + 2][1] = dp[i][0] + stairs[i + 2];
			if (dp[i + 2][1] < dp[i][1] + stairs[i + 2])
				dp[i + 2][1] = dp[i][1] + stairs[i + 2];
			if (dp[i + 2][1] < dp[i][2] + stairs[i + 2])
				dp[i + 2][1] = dp[i][2] + stairs[i + 2];
		}
	}

	cout << max(dp[N][2], dp[N][1]) << endl;

	return 0;
}