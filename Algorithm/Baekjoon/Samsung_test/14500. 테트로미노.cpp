#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 500
int N, M;
int map[MAX][MAX] = { 0, };
bool visited[MAX][MAX];
int rst = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int dy2[][4] = { { 0,1,1,1 },{ 1,0,1,2 },{ 0,0,0,1 },{ 0,1,2,1 } };
int dx2[][4] = { { 1,0,1,2 },{ 0,1,1,1 },{ 0,1,2,1 },{ 0,0,0,1 } };

void dfs(int y, int x, int cnt, int val) {
	if (cnt == 4) {
		rst = max(rst, val);
		return;
	}
	visited[y][x] = true;
	int nval = val + map[y][x];

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;
		if (!visited[ny][nx]) {
			visited[ny][nx] = true;
			dfs(ny, nx, cnt + 1, nval);
			visited[ny][nx] = false;
		}
	}
	visited[y][x] = false;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	int tmp = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dfs(i, j, 0, 0);

			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 4; l++) {
					int ny = i + dy2[k][l];
					int nx = j + dx2[k][l];
					if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
						tmp = 0;
						break;
					}
					tmp += map[ny][nx];
				}
				rst = max(rst, tmp);
				tmp = 0;
			}
		}
	}
	cout << rst << endl;
}