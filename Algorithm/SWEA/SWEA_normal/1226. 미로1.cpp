#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 16
int map[MAX][MAX];
bool visited[MAX][MAX];
int sy, sx, gy, gx;
int rst;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

void bfs() {
	queue<pair<int, int>>q;
	q.push(make_pair(sy, sx));

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		visited[y][x] = true;

		if (y == gy && x == gx) {
			rst = 1;
			return;
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX)continue;
			if ((map[ny][nx] == 0 || map[ny][nx] == 3) && !visited[ny][nx]) {
				visited[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

int main() {
	int T = 0;

	while (T < 10) {
		scanf("%d", &T);
		rst = 0;	//일단 불가능
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				scanf("%1d", &map[i][j]);

				if (map[i][j] == 2) {
					sy = i;
					sx = j;
				}
				else if (map[i][j] == 3) {
					gy = i;
					gx = j;
				}
			}
		}

		bfs();
		printf("#%d %d\n", T, rst);
	}

	return 0;
}