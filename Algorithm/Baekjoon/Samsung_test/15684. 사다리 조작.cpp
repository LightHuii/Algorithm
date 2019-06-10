#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 30
bool ladder[MAX + 1][10];
int N, M, H;
int rst = INT32_MAX;

bool check() {
	bool flag = false;
	int n;
	for (int i = 1; i <= N; i++) {
		n = i;

		for (int j = 1; j <= H; j++) {
			if (n > 1 && ladder[j][n - 1])
				n--;
			else if (n < N && ladder[j][n])
				n++;
		}
		if (n != i)return false;
	}
	return true;
}

void dfs(int h, int n, int cnt, bool chk) {
	if (cnt > 3 || cnt >= rst)return;
	else if (chk && cnt <= 3 && check()) {
		rst = min(rst, cnt);
		return;
	}
	if (h > H)return;

	int nh = h, nn = n + 1;
	if (nn > N) {
		nn = 1;
		nh++;
	}

	//오른 쪽 판단
	if (n < N && !ladder[h][n]) {
		if (n > 1 && n <= N - 2 && !ladder[h][n - 1] && !ladder[h][n + 1]) {
			ladder[h][n] = true;
			dfs(nh, nn, cnt + 1, true);
			ladder[h][n] = false;
		}
		else if (n == 1 && !ladder[h][n + 1]) {
			ladder[h][n] = true;
			dfs(nh, nn, cnt + 1, true);
			ladder[h][n] = false;
		}
	}
	//왼 쪽 판단
	else if (n > 1 && !ladder[h][n - 1]) {
		if (n > 2 && n <= N - 1 && !ladder[h][n - 2] && !ladder[h][n]) {
			ladder[h][n - 1] = true;
			dfs(nh, nn, cnt + 1, true);
			ladder[h][n - 1] = false;
		}
		else if (n == N && !ladder[h][n - 1]) {
			ladder[h][n - 1] = true;
			dfs(nh, nn, cnt + 1, true);
			ladder[h][n - 1] = false;
		}
	}

	dfs(nh, nn, cnt, false);
}

int main() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		ladder[a][b] = true;
	}

	dfs(1, 1, 0, true);
	if (rst == INT32_MAX)
		cout << -1 << endl;
	else
		cout << rst << endl;

	return 0;
}
​