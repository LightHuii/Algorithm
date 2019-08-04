#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

typedef struct a {
	int y, x, dir, cnt;
}Raser;

#define MAX 100
char map[MAX][MAX];
int H, W;
vector<pair<int, int>>v;	//시작점, 도착점
int visited[MAX][MAX] = { 0, };		//현재까지 사용한 거울의 개수로 표시
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };	//북동남서

int bfs() {
	queue<Raser>q;
	for (int i = 0; i < 4; i++) {
		Raser tmp = { v[0].first, v[0].second, i, 0 };	//처음은 모든 방향에 대해
		q.push(tmp);
	}

	int rst = INT32_MAX;	//최소 거울 개수 저장
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int dir = q.front().dir;
		int cnt = q.front().cnt;
		q.pop();

		//목적지 도착
		if (y == v[1].first && x == v[1].second) {
			rst = min(rst, cnt);
			continue;
		}

		//다음 좌표 탐색
		int ny, nx, nd;
		for (int i = 0; i < 4; i++) {
			if (i == 2)continue;	//반대 방향은 무시
			nd = (dir + i) % 4;
			ny = y + dy[nd];
			nx = x + dx[nd];
			if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;

			//직진할 차례일 때
			if (i == 0) {
				if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] > cnt)) {
					visited[ny][nx] = cnt;
					Raser tmp = { ny, nx, nd, cnt };	//카운트하지 않고 지나간다.
					q.push(tmp);
				}
			}
			//방향을 전환해야 할 때
			else {
				if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] >= cnt + 1)) {
					visited[ny][nx] = cnt + 1;
					Raser tmp = { ny, nx, nd, cnt + 1 };	//카운트하고 지나간다.
					q.push(tmp);
				}
			}
		}

	}

	return rst;
}

int main()
{
	cin >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'C')
				v.push_back(make_pair(i, j));
		}
	}

	cout << bfs() << endl;
}