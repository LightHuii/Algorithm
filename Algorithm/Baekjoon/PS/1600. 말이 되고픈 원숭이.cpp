#include<iostream>
#include<algorithm>
#include<queue>
#include<tuple>
using namespace std;

#define MAX 200
int map[MAX][MAX];
bool visited[31][MAX][MAX];	//첫 번째 차원은 말처럼 움직인 횟수에 따른 layer다
int K, W, H;
int rst = INT32_MAX;
int dy1[] = { 0,0,-1,1 };
int dx1[] = { -1,1,0,0 };
int dy2[] = { 2,2,1,1,-2,-2,-1,-1 };
int dx2[] = { 1,-1,2,-2,1,-1,2,-2 };

void bfs() {
	queue<tuple<int, int, int, int>>q;	//좌표, 횟수, 남은 시도횟수
	q.push(make_tuple(0, 0, 0, K));
	visited[K][0][0] = true;

	while (!q.empty()) {
		int y = get<0>(q.front());
		int x = get<1>(q.front());
		int cnt = get<2>(q.front());
		int trial = get<3>(q.front());
		q.pop();

		//도착하면 최소 값 갱신
		if (y == H - 1 && x == W - 1)
			rst = min(rst, cnt);

		//아직 말처럼 움직일 수 있는 기회가 남아 있다면
		if (trial > 0) {
			for (int i = 0; i < 8; i++) {
				int ny = y + dy2[i];
				int nx = x + dx2[i];
				if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
				if (!visited[trial - 1][ny][nx] && map[ny][nx] == 0) {
					visited[trial - 1][ny][nx] = true;
					q.push(make_tuple(ny, nx, cnt + 1, trial - 1));
				}
			}
		}

		//원숭이로 이동
		for (int i = 0; i < 4; i++) {
			int ny = y + dy1[i];
			int nx = x + dx1[i];
			if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
			if (!visited[trial][ny][nx] && map[ny][nx] == 0) {
				visited[trial][ny][nx] = true;
				q.push(make_tuple(ny, nx, cnt + 1, trial));
			}
		}
	}
}

int main() {
	cin >> K;
	cin >> W >> H;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			cin >> map[i][j];

	bfs();

	if (rst == INT32_MAX)
		cout << -1 << endl;
	else
		cout << rst << endl;
	return 0;
}