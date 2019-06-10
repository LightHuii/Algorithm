#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>
using namespace std;

#define MAX 10
int T;
int N, M, C;
int map[MAX][MAX];
vector<int>v1, v2;
int rst1 = 0, rst2 = 0;
int tmp1[5], tmp2[5];
int result = 0;

void dfs2(int idx, int cnt, int sum) {
	int t = 0;
	for (int i = 0; i < cnt; i++)
		t += tmp1[i] * tmp1[i];
	rst1 = max(rst1, t);

	if (idx >= M)
		return;

	tmp1[cnt] = v1[idx];
	if (sum + v1[idx] <= C)
		dfs2(idx + 1, cnt + 1, sum + v1[idx]);
	tmp1[cnt] = 0;
	dfs2(idx + 1, cnt, sum);
}

void dfs3(int idx, int cnt, int sum) {
	int t = 0;
	for (int i = 0; i < cnt; i++)
		t += tmp2[i] * tmp2[i];
	rst2 = max(rst2, t);

	if (idx >= M)
		return;

	tmp2[cnt] = v2[idx];
	if (sum + v2[idx] <= C)
		dfs3(idx + 1, cnt + 1, sum + v2[idx]);
	tmp2[cnt] = 0;
	dfs3(idx + 1, cnt, sum);
}

void dfs(int cnt, int y, int x) {
	if (cnt == 2) {
		//½ÇÇà
		rst1 = 0;
		rst2 = 0;

		dfs2(0, 0, 0);
		dfs3(0, 0, 0);
		result = max(result, rst1 + rst2);
		return;
	}

	while (1) {
		if (cnt == 0) {
			for (int i = 0; i < M; i++)v1.push_back(map[y][x + i]);

			int ny = y;
			int nx = x + M;
			if (nx > N - M) {
				nx = 0;
				ny++;
				if (ny >= N)break;
			}
			dfs(cnt + 1, ny, nx);

			v1.clear();

			x++;
			if (x > N - M) {
				x = 0;
				y++;
				if (y >= N)break;
			}
		}
		else if (cnt == 1) {
			for (int i = 0; i < M; i++)v2.push_back(map[y][x + i]);

			int ny = y;
			int nx = x + 1;
			if (nx > N - M) {
				nx = 0;
				ny++;
			}

			dfs(cnt + 1, ny, nx);
			v2.clear();

			if (ny >= N)
				break;

			x++;
			if (x > N - M) {
				if (y == N - 1)	continue;

				y++;
				x = 0;
				if (y >= N)break;
			}
		}
	}
}

int main() {
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		result = 0;
		memset(tmp1, 0, sizeof(tmp1));
		memset(tmp2, 0, sizeof(tmp2));
		v1.clear();
		v2.clear();

		cin >> N >> M >> C;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		dfs(0, 0, 0);
		cout << '#' << T - Ttmp << ' ' << result << endl;
	}

	return 0;
}