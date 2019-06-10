#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 15
int map[MAX + 1][MAX] = { 0, };
bool visited[MAX][MAX];
int N, M, D;
int archer[3];
int dy[] = { 0,-1,0 };
int dx[] = { -1,0,1 };	//서 북 동
vector<pair<int, int>>v;	//적이 있는 좌표 저장: 중복됨
int rst = 0;
int tmap[MAX + 1][MAX];

void move() {
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			tmap[i + 1][j] = tmap[i][j];
			tmap[i][j] = 0;
		}
	}
}

void bfs(int y, int x) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	int r = 0;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			y = q.front().first;
			x = q.front().second;
			q.pop();

			if (tmap[y][x] == 1) {
				v.push_back(make_pair(y, x));
				return;
			}
			for (int i = 0; i < 3; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;
				if (!visited[ny][nx]) {
					visited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}

		r++;
		if (r == D + 1)return;	//범위만큼 했으면 끝내기
	}
}

void dfs(int cnt, int idx) {
	if (cnt == 3) {
		//실행
		memcpy(tmap, map, sizeof(map));	 //임시로 맵 사용

		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			v.clear();
			for (int j = 0; j < 3; j++) {
				memset(visited, false, sizeof(visited));
				bfs(N, archer[j]);	//각 궁수의 좌표에 대해 bfs 실행
			}

			for (int j = 0; j < (int)v.size(); j++) {
				if (tmap[v[j].first][v[j].second] == 1) {
					tmap[v[j].first][v[j].second] = 0;
					cnt++;	//적을 없애고 카운트 증가
				}
			}

			//이제 적 이동
			move();
		}

		rst = max(rst, cnt);
		return;
	}
	if (idx >= M)return;

	archer[cnt] = idx;
	dfs(cnt + 1, idx + 1);
	dfs(cnt, idx + 1);
}

int main() {
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	dfs(0, 0);

	cout << rst << endl;
	return 0;
}