#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

#define MAX 21
int N;
int S[MAX][MAX];
bool selected[MAX];
int rst = INT32_MAX;

void dfs(int cnt, int idx) {
	if (cnt == N / 2) {
		int a = 0, b = 0;

		for (int i = 1; i <= N; i++) {
			if (!selected[i]) {
				for (int j = 1; j <= N; j++) {
					if (i == j)continue;
					if (!selected[j])
						a += S[i][j];
				}
			}
			else {
				for (int j = 1; j <= N; j++) {
					if (i == j)continue;
					if (selected[j])
						b += S[i][j];
				}
			}
		}

		rst = min(rst, abs(a - b));
		return;
	}
	if (idx >= N)return;

	if (!selected[idx]) {
		selected[idx] = true;
		dfs(cnt + 1, idx + 1);
		selected[idx] = false;
	}
	dfs(cnt, idx + 1);
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> S[i][j];

	dfs(0, 1);

	cout << rst << endl;
	return 0;
}