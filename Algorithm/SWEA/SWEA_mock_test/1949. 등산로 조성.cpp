#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
using namespace std;

#define MAX 8
int map[MAX][MAX];
bool visited[MAX][MAX];
int T, N, K;
int rst = 0;
vector<pair<int, int>>v;

int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

void dfs(int y, int x, int cnt) {
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
		if (!visited[ny][nx] && map[ny][nx] < map[y][x]) {
			flag = true;
			visited[ny][nx] = true;
			dfs(ny, nx, cnt + 1);
			visited[ny][nx] = false;
		}
	}
	//종료 조건
	if (!flag) {
		rst = max(rst, cnt);
		return;
	}
}

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {
		rst = 0;
		cin >> N >> K;

		int highest = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				highest = max(highest, map[i][j]);
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int p = 0; p <= K; p++) {
					int tmp = map[i][j];
					map[i][j] -= p;
					if (map[i][j] < 0) map[i][j] = 0;


					for (int k = 0; k < N; k++) {
						for (int l = 0; l < N; l++) {
							if (map[k][l] != highest)continue;
							visited[k][l] = true;
							dfs(k, l, 1);
							visited[k][l] = false;
							memset(visited, false, sizeof(visited));
						}
					}
					if (map[i][j] != 0)
						map[i][j] += p;
					else
						map[i][j] = tmp;
				}
			}
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}
	return 0;
}