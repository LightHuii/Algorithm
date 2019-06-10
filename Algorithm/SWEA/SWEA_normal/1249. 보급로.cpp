#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
using namespace std;

int map[100][100];
int dist[100][100];
bool visited[100][100];
int T, N;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

//다익스트라 원리로 bfs 구현
void bfs() {
	queue<pair<int, int>>q;
	q.push(make_pair(0, 0));
	visited[0][0] = true;

	while (!q.empty()) {
		int size = q.size();

		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		//다음 노드들에 대해
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;

			//들리지 않았거나 더 짧은 거리가가능할 때
			if (!visited[ny][nx] || dist[ny][nx] > dist[y][x] + map[ny][nx]) {
				dist[ny][nx] = dist[y][x] + map[ny][nx];
				q.push(make_pair(ny, nx));
				//-> 여기서 최단거리가 아닐지라도 push는 됨: 필요 없는 값

				visited[ny][nx] = true;
			}
		}
	}
}

int main() {
	scanf("%d", &T);
	int Ttmp = T;

	while (Ttmp--) {
		scanf("%d", &N);

		//초기화
		memset(visited, false, sizeof(visited));
		memset(map, 0, sizeof(map));

		//처음 위치를 제외한 모든 노드들의 거리는 모르는 상태
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dist[i][j] = INT32_MAX;
		dist[0][0] = 0;

		//입력
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%1d", &map[i][j]);
			}
		}

		bfs();
		printf("#%d %d\n", T - Ttmp, dist[N - 1][N - 1]);
	}


	return 0;
}