#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
#include<tuple>
using namespace std;

#define MAX 30
char map[MAX][MAX][MAX];
bool visited[MAX][MAX][MAX];
int sz, sy, sx, ez, ey, ex;	//시작, 도착 지점의 좌표
int L, R, C;
int dz[] = { -1,1,0,0,0,0 };
int dy[] = { 0,0,-1,1,0,0 };
int dx[] = { 0,0,0,0,-1,1 };

int bfs() {
	queue<tuple<int, int, int>>q;
	q.push(make_tuple(sz, sy, sx));

	//거리
	int dist = 0;

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int z = get<0>(q.front());
			int y = get<1>(q.front());
			int x = get<2>(q.front());
			q.pop();

			//cout << z << ", " << y << ", " << x << endl;

			if (z == ez &&y == ey &&x == ex)
				return dist;

			visited[z][y][x] = true;
			
			for (int i = 0; i < 6; i++) {
				int nz = z + dz[i];
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (nz < 0 || nz >= L || ny < 0 || ny >= R || nx < 0 || nx >= C)continue;
				if (!visited[nz][ny][nx] && (map[nz][ny][nx] == '.' || map[nz][ny][nx] == 'E')) {
					visited[nz][ny][nx] = true;
					q.push(make_tuple(nz, ny, nx));
				}
			}
		}
		dist++;
	}

	return -1;
}

int main() {
	while (1) {
		cin >> L >> R >> C;
		if (L == 0 && R == 0 && C == 0) break;

		//초기화
		memset(visited, false, sizeof(visited));

		for (int k = 0; k < L; k++) {
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					cin >> map[k][i][j];
					if (map[k][i][j] == 'S') {
						sz = k;
						sy = i;
						sx = j;
					}
					else if (map[k][i][j] == 'E') {
						ez = k;
						ey = i;
						ex = j;
					}
				}
			}
		}
		int rst = bfs();
		if (rst == -1) cout << "Trapped!" << endl;
		else
			cout << "Escaped in " << rst << " minute(s)." << endl;

	}

	return 0;
}