#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 50
int map[MAX][MAX] = { 0, };
int tmap[MAX][MAX] = { 0, };
bool visited[MAX][MAX];
int R, C, T;
vector<pair<int, int>>aircon;	//공기 청정기 좌표
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

void initvisit() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] += tmap[i][j];
			tmap[i][j] = 0;
		}
	}
}

void move_air() {
	//위쪽 사이클
	int y = aircon[0].first;

	//shift down
	for (int i = y - 1; i > 0; i--)
		map[i][0] = map[i - 1][0];

	//shift left
	for (int i = 0; i < C - 1; i++)
		map[0][i] = map[0][i + 1];

	//shift up
	for (int i = 0; i <= y - 1; i++)
		map[i][C - 1] = map[i + 1][C - 1];

	//shift right
	for (int i = C - 1; i >= 2; i--)
		map[y][i] = map[y][i - 1];

	map[y][1] = 0;	//정화된 공기


					//아래 쪽 사이클
	y = aircon[1].first;

	//shift up
	for (int i = y + 1; i <= R - 2; i++)
		map[i][0] = map[i + 1][0];

	//shift left
	for (int i = 0; i <= C - 2; i++)
		map[R - 1][i] = map[R - 1][i + 1];

	//shift down
	for (int i = R - 1; i >= y + 1; i--)
		map[i][C - 1] = map[i - 1][C - 1];

	//shift right
	for (int i = C - 1; i >= 2; i--)
		map[y][i] = map[y][i - 1];

	map[y][1] = 0;
}

int main() {
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1)
				aircon.push_back(make_pair(i, j));
		}
	}

	for (int t = 0; t < T; t++) {
		//확산
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (map[i][j] < 5)continue;
				int cnt = 0;	//확산된 블록 수
				for (int d = 0; d < 4; d++) {
					int ny = i + dy[d];
					int nx = j + dx[d];
					if (ny < 0 || ny >= R || nx < 0 || nx >= C || map[ny][nx] == -1)continue;
					cnt++;
					tmap[ny][nx] += map[i][j] / 5;
				}
				map[i][j] -= (map[i][j] / 5)*cnt;
			}
		}
		initvisit();


		//공기청정기 가동
		move_air();
	}

	int rst = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			rst += map[i][j];
		}
	}

	rst += 2;
	cout << rst << endl;
	return 0;
}