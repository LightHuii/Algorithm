#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 200
int map[MAX][MAX];
int N, M, T;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
bool visited[MAX][MAX];

int bfs(int y, int x) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	int house = 0;
	int tmp = 0;
	int area = 0;
	int rst = 0;
	while (!q.empty()) {
		int size = q.size();
		area++;

		while (size--) {
			y = q.front().first;
			x = q.front().second;
			q.pop();
			visited[y][x] = true;
			if (map[y][x] == 1)house++;

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				if (!visited[ny][nx]) {
					visited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
		tmp += house;
		house = 0;

		//수지타산 맞으면
		if (area*area + (area - 1)*(area - 1) <= tmp*M)
			rst = max(rst, tmp);
	}
	return rst;
}

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {
		cin >> N >> M;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		int rst = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				rst = max(rst, bfs(i, j));
				memset(visited, false, sizeof(visited));
			}
		}

		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}
	return 0;
}
