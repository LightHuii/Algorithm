#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<tuple>
using namespace std;

int cube[5][5][5];		//입력
int cube_rst[5][5][5];	//bfs 실행할 큐브
int plate_tmp[5][5];	//회전된 판
bool selected[5];		//판 순서 체크
bool visited[5][5][5];	//bfs 체크
int rst = INT32_MAX;
int dz[] = { 0,0,-1,1,0,0 };
int dy[] = { 0,0,0,0,-1,1 };
int dx[] = { -1,1,0,0,0,0 };

//0: 그대로, 1: 시계 90도, 2: 반시계90도, 3: 180도
void rotate(int idx, int dir) {
	if (dir == 1) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				plate_tmp[i][j] = cube[idx][4 - j][i];
	}
	else if (dir == 2) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				plate_tmp[i][j] = cube[idx][j][4 - i];
	}
	else if (dir == 3) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				plate_tmp[i][j] = cube[idx][4 - i][4 - j];
	}
	else if (dir == 0) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				plate_tmp[i][j] = cube[idx][i][j];
	}
}

int bfs() {
	if (cube_rst[0][0][0] == 0)return INT32_MAX;

	memset(visited, false, sizeof(visited));
	queue<tuple<int, int, int>>q;
	q.push(make_tuple(0, 0, 0));

	int cnt = 0;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int z = get<0>(q.front());
			int y = get<1>(q.front());
			int x = get<2>(q.front());
			q.pop();
			visited[z][y][x] = true;

			//마지막에 도달하면 리턴
			if (z == 4 && y == 4 && x == 4) return cnt;

			for (int i = 0; i < 6; i++) {
				int nz = z + dz[i];
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (nz < 0 || nz >= 5 || ny < 0 || ny >= 5 || nx < 0 || nx >= 5)continue;
				if (!visited[nz][ny][nx] && cube_rst[nz][ny][nx] == 1) {
					visited[nz][ny][nx] = true;
					q.push(make_tuple(nz, ny, nx));
				}
			}
		}

		cnt++;
	}
	return INT32_MAX;
}

//cnt: 순서, 방향이 결정된 판의 수
void dfs(int cnt) {
	//모두 정해졌을 때
	if (cnt == 5) {
		int tmp = bfs();
		rst = min(rst, tmp);
		return;
	}

	//판의 순서 결정
	for (int i = 0; i < 5; i++) {
		if (selected[i])continue;
		selected[i] = true;

		//회전 및 삽입
		for (int j = 0; j < 4; j++) {
			rotate(i, j);

			//큐브에 판 삽입
			for (int y = 0; y < 5; y++)
				for (int x = 0; x < 5; x++)
					cube_rst[cnt][y][x] = plate_tmp[y][x];

			dfs(cnt + 1);
		}
		selected[i] = false;
	}
}

int main() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				cin >> cube[i][j][k];

	dfs(0);
	if (rst == INT32_MAX)
		cout << -1 << endl;
	else
		cout << rst << endl;

	return 0;
}