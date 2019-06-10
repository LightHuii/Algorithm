#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 50
int T, N, M, R, C, L;	//¼¼·Î, °¡·Î, ¸ÇÈ¦ À§Ä¡, Å»Ãâ ½Ã°£
int map[MAX][MAX] = { 0, };
bool visited[MAX][MAX];
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };	//¼­ µ¿ ºÏ ³²

bool check(int y, int x, int dir) {
	int curr = map[y][x];
	int next = map[y + dy[dir]][x + dx[dir]];

	if (next == 0)return false;
	else if (curr == 1) {
		if (dir == 0) {
			if (next == 1 || next == 3 || next == 4 || next == 5)return true;
			else return false;
		}
		else if (dir == 1) {
			if (next == 1 || next == 3 || next == 6 || next == 7)return true;
			else return false;
		}
		else if (dir == 2) {
			if (next == 1 || next == 2 || next == 5 || next == 6)return true;
			else return false;
		}
		else if (dir == 3) {
			if (next == 1 || next == 2 || next == 4 || next == 7)return true;
			else return false;
		}
	}
	else if (curr == 2) {
		if (dir == 0 || dir == 1)return false;
		else if (dir == 2) {
			if (next == 2 || next == 1 || next == 6 || next == 5)return true;
			else return false;
		}
		else if (dir == 3) {
			if (next == 2 || next == 1 || next == 4 || next == 7)return true;
			else return false;
		}
	}
	else if (curr == 3) {
		if (dir == 2 || dir == 3)return false;
		else if (dir == 0) {
			if (next == 3 || next == 1 || next == 4 || next == 5)return true;
			else return false;
		}
		else if (dir == 1) {
			if (next == 3 || next == 1 || next == 6 || next == 7)return true;
			else return false;
		}
	}
	else if (curr == 4) {
		if (dir == 0 || dir == 3)return false;
		else if (dir == 1) {
			if (next == 1 || next == 3 || next == 6 || next == 7)return true;
			else return false;
		}
		else if (dir == 2) {
			if (next == 1 || next == 2 || next == 5 || next == 6)return true;
			else return false;
		}
	}
	else if (curr == 5) {
		if (dir == 0 || dir == 2)return false;
		else if (dir == 1) {
			if (next == 1 || next == 3 || next == 6 || next == 7)return true;
			else return false;
		}
		else if (dir == 3) {
			if (next == 1 || next == 2 || next == 4 || next == 7)return true;
			else return false;
		}
	}
	else if (curr == 6) {
		if (dir == 1 || dir == 2)return false;
		else if (dir == 0) {
			if (next == 1 || next == 3 || next == 4 || next == 5)return true;
			else return false;
		}
		else if (dir == 3) {
			if (next == 1 || next == 2 || next == 4 || next == 7)return true;
			else return false;
		}
	}
	else if (curr == 7) {
		if (dir == 1 || dir == 3)return false;
		else if (dir == 0) {
			if (next == 1 || next == 3 || next == 4 || next == 5)return true;
			else return false;
		}
		else if (dir == 2) {
			if (next == 1 || next == 2 || next == 5 || next == 6)return true;
			else return false;
		}
	}

	return false;
}

int bfs(int y, int x) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));
	int cnt = 0, t = 0;

	while (!q.empty()) {
		int size = q.size();

		while (size--) {
			y = q.front().first;
			x = q.front().second;
			q.pop();

			if (t == L)return cnt;

			//cout << "y, x: " << y << ", " << x << endl;


			visited[y][x] = true;
			cnt++;

			for (int d = 0; d < 4; d++) {
				int ny = y + dy[d];
				int nx = x + dx[d];
				if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;

				if (check(y, x, d) && !visited[ny][nx]) {
					visited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
		t++;
	}
	return cnt;
}

int main() {
	int rst;

	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		memset(visited, false, sizeof(visited));
		rst = 0;
		cin >> N >> M >> R >> C >> L;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> map[i][j];

		rst = bfs(R, C);

		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}