#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef struct node {
	int y, x, s, d, z;
	bool live;
}fish;
int R, C, M;
int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0,0,0,1,-1 };	//북 남 동 서
fish F[10001];
int rst = 0;

int map[101][101] = { 0, };

void hunt(int x) {
	int y = 1;
	while (map[y][x] == 0 && y <= R)y++;

	if (y <= R && map[y][x] > 0) {
		rst += F[map[y][x]].z;
		F[map[y][x]].live = false;
		//cout << map[y][x] << endl << endl;
		map[y][x] = 0;
	}
}

void eat() {
	for (int i = 1; i <= M; i++) {
		if (!F[i].live)continue;
		int ty = F[i].y;
		int tx = F[i].x;

		if (map[ty][tx] != 0) {
			int other = map[ty][tx];
			if (F[other].live) {
				if (F[i].z < F[other].z) {
					F[i].live = false;
					map[ty][tx] = other;
				}
				else if (F[i].z > F[other].z) {
					map[ty][tx] = i;
					F[other].live = false;
				}
			}
		}
		else
			map[ty][tx] = i;
	}
}

void movFish() {
	for (int i = 1; i <= M; i++) {
		if (!F[i].live)continue;

		int y = F[i].y;
		int x = F[i].x;
		int ty = y;
		int tx = x;
		int d = F[i].d;

		for (int j = 0; j < F[i].s; j++) {
			int ny = ty + dy[d];
			int nx = tx + dx[d];

			if (ny <= 0) {
				d = 2;
				ny = ty + dy[d];
				nx = tx + dx[d];
			}
			else if (ny > R) {
				d = 1;
				ny = ty + dy[d];
				nx = tx + dx[d];
			}
			else if (nx <= 0) {
				d = 3;
				ny = ty + dy[d];
				nx = tx + dx[d];
			}
			else if (nx > C) {
				d = 4;
				ny = ty + dy[d];
				nx = tx + dx[d];
			}
			ty = ny;
			tx = nx;

		}

		F[i].y = ty;
		F[i].x = tx;
		F[i].d = d;
		//일단 이동 후, 맵에는 표시X
		map[y][x] = 0;
	}
}

int main() {
	cin >> R >> C >> M;
	int r, c, s, d, z;
	for (int i = 1; i <= M; i++) {
		cin >> r >> c >> s >> d >> z;
		F[i].y = r;
		F[i].x = c;
		F[i].s = s;
		F[i].d = d;
		F[i].z = z;
		F[i].live = true;
		map[r][c] = i;
	}

	for (int i = 1; i <= C; i++) {
		hunt(i);

		movFish();
		eat();
	}
	cout << rst << endl;
	return 0;
}