#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 50
int map[MAX][MAX];
int visited[MAX][MAX] = { 0, };
int y, x, d;	//현재 좌표, 방향
int N, M;
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

int main() {
	cin >> N >> M;
	cin >> y >> x >> d;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	int cnt = 0;	//청소한 칸의 개수
	int ny = y, nx = x, nd = d;	//다음 좌표와 방향

	while (1) {
		//청소한다.
		if (map[y][x] == 0 && visited[y][x] == 0) {
			cnt++;
			visited[y][x] = cnt;
		}


		//왼 쪽 탐색
		nd = d - 1;
		if (nd < 0)nd = 3;

		ny = y + dy[nd];
		nx = x + dx[nd];	//다음 좌표

							//청소할 수 있다면 직진
		if (map[ny][nx] == 0 && visited[ny][nx] == 0) {
			d = nd;	//회전
			y = ny;
			x = nx;
			continue;
		}
		//청소할 수 없다면
		else {
			int tmp_cnt = 0;
			while (map[ny][nx] != 0 || visited[ny][nx] != 0) {		//왼 쪽을 청소할 수 없는 동안
																	//왼 쪽 탐색
				nd = nd - 1;
				if (nd < 0)nd = 3;

				ny = y + dy[nd];
				nx = x + dx[nd];	//다음 좌표
				tmp_cnt++;	//돈 횟수
				if (tmp_cnt == 4)break;
			}
			if (tmp_cnt == 4) {
				//후진
				nd = (d + 2) % 4;
				if (map[y + dy[nd]][x + dx[nd]] == 1)
					break;
				y = y + dy[nd];
				x = x + dx[nd];
				nd = d;
				continue;
			}
			d = (nd + 1) % 4;
		}
	}

	cout << cnt << endl;

	return 0;
}