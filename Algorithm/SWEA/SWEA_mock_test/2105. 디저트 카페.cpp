#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 20
int T, N;
int map[MAX][MAX];
int rst;
bool visitnum[101];
bool visited[MAX][MAX];

int dy[] = { 1,1,-1,-1 };
int dx[] = { 1,-1,-1,1 };

//시계 방향 회전
void dfs1(int cnt, int y, int x, int oy, int ox, int dir, int dnum) {
	//종료 조건1
	if (y == oy && x == ox && cnt > 1) {
		rst = max(rst, cnt);
		return;
	}
	//종료 조건2
	if (dnum > 3 || visitnum[map[y][x]] || visited[y][x])
		return;

	visitnum[map[y][x]] = true;
	visited[y][x] = true;

	bool tmpnum[101];
	bool tmpvisit[MAX][MAX];

	memcpy(tmpnum, visitnum, sizeof(tmpnum));
	memcpy(tmpvisit, visited, sizeof(tmpvisit));

	int ndir = (dir + 1) % 4;
	int ny = y + dy[ndir];
	int nx = x + dx[ndir];
	if (ny >= 0 && ny < N && nx >= 0 && nx < N)
		dfs1(cnt + 1, ny, nx, oy, ox, ndir, dnum + 1);

	memcpy(visitnum, tmpnum, sizeof(tmpnum));
	memcpy(visited, tmpvisit, sizeof(tmpvisit));

	ndir = dir;
	ny = y + dy[ndir];
	nx = x + dx[ndir];
	if (ny >= 0 && ny < N && nx >= 0 && nx < N)
		dfs1(cnt + 1, ny, nx, oy, ox, ndir, dnum);
}

//반시계 방향 회전
void dfs2(int cnt, int y, int x, int oy, int ox, int dir, int dnum) {
	//종료 조건1
	if (y == oy && x == ox && cnt > 1) {
		rst = max(rst, cnt);
		return;
	}
	//종료 조건2
	if (dnum > 3 || visitnum[map[y][x]] || visited[y][x])
		return;

	visitnum[map[y][x]] = true;
	visited[y][x] = true;

	bool tmpnum[101];
	bool tmpvisit[MAX][MAX];

	memcpy(tmpnum, visitnum, sizeof(tmpnum));
	memcpy(tmpvisit, visited, sizeof(tmpvisit));

	int ndir = dir - 1;
	if (ndir < 0)ndir = 3;
	int ny = y + dy[ndir];
	int nx = x + dx[ndir];

	if (ny >= 0 && ny < N && nx >= 0 && nx < N)
		dfs2(cnt + 1, ny, nx, oy, ox, ndir, dnum + 1);

	memcpy(visitnum, tmpnum, sizeof(tmpnum));
	memcpy(visited, tmpvisit, sizeof(tmpvisit));

	ndir = dir;
	ny = y + dy[ndir];
	nx = x + dx[ndir];
	if (ny >= 0 && ny < N && nx >= 0 && nx < N)
		dfs2(cnt + 1, ny, nx, oy, ox, ndir, dnum);
}

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {
		rst = 0;
		memset(visited, false, sizeof(visited));
		memset(visitnum, false, sizeof(visitnum));

		cin >> N;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		//모든 좌표, 모든 방향에 대해 실시
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int d = 0; d < 4; d++) {
					dfs1(0, i, j, i, j, d, 0);
					dfs2(0, i, j, i, j, d, 0);
					memset(visited, false, sizeof(visited));
					memset(visitnum, false, sizeof(visitnum));
				}
		if (rst == 0)
			rst = -1;
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}