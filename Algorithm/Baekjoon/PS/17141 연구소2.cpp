#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>
#include<time.h>
using namespace std;

#define MAX 50
int map_origin[MAX][MAX];
int map[MAX][MAX];
int visited[MAX][MAX];
int N, M;
vector<pair<int, int>>virus_poten;
int poten_cnt = 0;
pair<int, int>virus[11];
int rst = INT32_MAX;
int zero = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

int bfs() {
	queue<pair<int, int>>q;

	//미리 바이러스를 큐에 저장하고, 바이러스 위치를 표시한다
	for (int i = 0; i < M; i++) {
		q.push(virus[i]);
		map[virus[i].first][virus[i].second] = 2;	//바이러스 표시
	}

	int t = 0;	//시간
	int zero2 = zero - M;	//빈 공간의 수

	while (!q.empty()) {
		int size = q.size();

		//한 사이클 실행
		while (size--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			//처음부터 빈공간이 없는 경우
			if (zero2 == 0)
				return t;

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				if (map[ny][nx] == 0 && visited[ny][nx] == 0) {
					visited[ny][nx] = visited[y][x] + 1;
					q.push(make_pair(ny, nx));
					zero2--;	//빈 공간 하나 감소

					if (zero2 == 0)	//빈 공간이 더이상 없다면 종료
						return t + 1;
				}
			}
		}
		t++;	//시간 증가
	}

	return -1;
}

void dfs(int cnt, int idx) {
	if (idx >= poten_cnt) {
		if (cnt == M) {
			//bfs 수행
			memcpy(map, map_origin, sizeof(map));
			memset(visited, 0, sizeof(visited));
			int tmp = bfs();

			//한 번이라도 제대로 수행되지 않는다면 rst의 값은 그대로
			if (tmp > -1)
				rst = min(rst, tmp);
		}
		return;
	}

	virus[cnt] = virus_poten[idx];
	dfs(cnt + 1, idx + 1);
	dfs(cnt, idx + 1);
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map_origin[i][j];

			//바이러스를 놓을 수 있는 곳
			if (map_origin[i][j] == 2) {
				zero++;
				poten_cnt++;
				virus_poten.push_back(make_pair(i, j));
				map_origin[i][j] = 0;	//바이러스 가능 공간 확인 후 빈 공간으로 만든다
			}
			else if (map_origin[i][j] == 0)
				zero++;
		}
	}

	dfs(0, 0);

	if (rst != INT32_MAX)
		cout << rst << endl;
	else
		cout << -1 << endl;
	return 0;
}