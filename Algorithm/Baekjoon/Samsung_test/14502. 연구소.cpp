#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<vector>
using namespace std;

#define MAX 8
int map[MAX][MAX];
int N, M;
int rst = 0;
int zero = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
vector<pair<int, int>>v;

void dfs(int y, int x, int wall_cnt) {
	if (wall_cnt == 3) {

		//실행
		bool visited[MAX][MAX] = { false, };
		int cnt = zero - 3;	//빈 공간의 개수

		queue<pair<int, int>>q;
		for (int i = 0; i < (int)v.size(); i++) {
			q.push(v[i]);
			visited[v[i].first][v[i].second] = true;
		}

		while (!q.empty()) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= M || map[ny][nx] != 0)continue;
				if (!visited[ny][nx]) {
					visited[ny][nx] = true;
					cnt--;
					q.push(make_pair(ny, nx));
				}
			}
		}
		rst = max(rst, cnt);
		return;
	}

	if (y >= N)return;

	int ny = y, nx = x;
	nx++;
	if (nx >= M) {
		nx = 0;
		ny++;
	}

	if (map[y][x] == 0) {
		map[y][x] = 1;
		dfs(ny, nx, wall_cnt + 1);
		map[y][x] = 0;
	}
	dfs(ny, nx, wall_cnt);
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2)
				v.push_back(make_pair(i, j));
			else if (map[i][j] == 0)
				zero++;
		}
	}

	dfs(0, 0, 0);

	cout << rst << endl;
	return 0;
}