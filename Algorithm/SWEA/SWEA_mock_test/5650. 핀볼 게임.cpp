#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 101
int T, N;
int map[MAX][MAX];
int rst;
int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };	//동0, 서1, 남2, 북3
pair<int, int>worm1[11];
pair<int, int>worm2[11];
int sy, sx;	//시작 좌표

void init() {
	rst = 0;
	for (int i = 0; i <= 10; i++) {
		worm1[i].first = -1;
		worm1[i].second = -1;
		worm2[i].first = -1;
		worm2[i].second = -1;
	}
}

//블록, 벽에 닿았을 때 방향 설정
//어느 좌표고, 어느 방향으로 왔는지, 어떤 블록인지
int set_dir(int y, int x, int dir, int block) {
	//벽일 경우
	if (block == 0) {
		if (y < 0)
			return 2;	//북->남
		else if (y >= N)
			return 3;	//남->북
		else if (x < 0)
			return 0;	//서->동
		else if (x >= N)
			return 1;	//동->서
	}
	//블록일 경우
	else {
		if (block == 1) {
			if (dir == 3)
				return 2;	//북 -> 남
			else if (dir == 0)
				return 1;	//동 -> 서
			else if (dir == 2)
				return 0;	//남 -> 동
			else if (dir == 1)
				return 3;	//서 -> 북
		}
		else if (block == 2) {
			if (dir == 3)
				return 0;	//북 -> 동
			else if (dir == 0)
				return 1;	//동 -> 서
			else if (dir == 2)
				return 3;	//남 -> 북
			else if (dir == 1)
				return 2;	//서 -> 남
		}
		else if (block == 3) {
			if (dir == 3)
				return 1;	//북 -> 서
			else if (dir == 0)
				return 2;	//동 -> 남
			else if (dir == 2)
				return 3;	//남 -> 북
			else if (dir == 1)
				return 0;	//서 -> 동
		}
		else if (block == 4) {
			if (dir == 3)
				return 2;	//북 -> 남
			else if (dir == 0)
				return 3;	//동 -> 북
			else if (dir == 2)
				return 1;	//남 -> 서
			else if (dir == 1)
				return 0;	//서 -> 동
		}
		else if (block == 5) {
			if (dir == 3)
				return 2;	//북 -> 남
			else if (dir == 0)
				return 1;	//동 -> 서
			else if (dir == 2)
				return 3;	//남 -> 북
			else if (dir == 1)
				return 0;	//서 -> 동
		}
	}
	return 0;
}

void run(int y, int x, int dir) {
	//일단 한 칸 이동
	int cy = y;
	int cx = x;
	int score = 0;

	//일단 직진하고, 현재 좌표에 대해 판단하기

	while (1) {
		//직진
		cy += dy[dir];
		cx += dx[dir];

		//cout << "y, x: " << cy << ", " << cx << endl;
		//cout << "score: " << score << endl;
		//cout << "sy, sx: " << sy << ", " << sx << endl << endl;;

		//종료 조건일 때
		if ((cy == sy && cx == sx) || map[cy][cx] == -1) {
			rst = max(rst, score);
			break;
		}

		//벽일 때
		if (cy < 0 || cx < 0 || cy >= N || cx >= N) {
			dir = set_dir(cy, cx, dir, 0);
			score++;
		}
		//블록일 때
		else if (map[cy][cx] >= 1 && map[cy][cx] <= 5) {
			dir = set_dir(cy, cx, dir, map[cy][cx]);
			score++;
		}
		//웜홀일 경우
		else if (map[cy][cx] >= 6 && map[cy][cx] <= 10) {
			int ty, tx;
			if (worm1[map[cy][cx]].first == cy && worm1[map[cy][cx]].second == cx) {
				ty = worm2[map[cy][cx]].first;
				tx = worm2[map[cy][cx]].second;
				cy = ty;
				cx = tx;
			}
			else if (worm2[map[cy][cx]].first == cy && worm2[map[cy][cx]].second == cx) {
				ty = worm1[map[cy][cx]].first;
				tx = worm1[map[cy][cx]].second;
				cy = ty;
				cx = tx;
			}
		}
	}
}

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	init();

	while (Ttmp--) {
		cin >> N;

		//입력
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];

				//웜홀 이라면
				if (map[i][j] >= 6 && map[i][j] <= 10) {
					if (worm1[map[i][j]].first == -1) {
						worm1[map[i][j]].first = i;
						worm1[map[i][j]].second = j;
					}
					else {
						worm2[map[i][j]].first = i;
						worm2[map[i][j]].second = j;
					}
				}
			}
		}


		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int d = 0; d < 4; d++) {
					sy = i;
					sx = j;	//시작점 설정
							//블록, 웜홀, 블랙홀일 경우 제외
					if (map[i][j] == -1 || (map[i][j] >= 1 && map[i][j] <= 10))continue;
					run(i, j, d);
				}
			}
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
		init();
	}
}