#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 20
int N, M, K, Y, X;
int map[MAX][MAX] = { 0, };
int cube[6] = { 0, };
int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };

void func(int d) {
	int tmp_cube[6] = { 0, };

	switch (d)
	{
	case 1:
		tmp_cube[0] = cube[4];
		tmp_cube[1] = cube[1];
		tmp_cube[2] = cube[5];
		tmp_cube[3] = cube[3];
		tmp_cube[4] = cube[2];
		tmp_cube[5] = cube[0];
		break;
	case 2:
		tmp_cube[0] = cube[5];
		tmp_cube[1] = cube[1];
		tmp_cube[2] = cube[4];
		tmp_cube[3] = cube[3];
		tmp_cube[4] = cube[0];
		tmp_cube[5] = cube[2];
		break;
	case 3:
		tmp_cube[0] = cube[1];
		tmp_cube[1] = cube[2];
		tmp_cube[2] = cube[3];
		tmp_cube[3] = cube[0];
		tmp_cube[4] = cube[4];
		tmp_cube[5] = cube[5];
		break;
	case 4:
		tmp_cube[0] = cube[3];
		tmp_cube[1] = cube[0];
		tmp_cube[2] = cube[1];
		tmp_cube[3] = cube[2];
		tmp_cube[4] = cube[4];
		tmp_cube[5] = cube[5];
		break;
	default:
		break;
	}

	for (int i = 0; i < 6; i++)
		cube[i] = tmp_cube[i];
}

int main() {
	cin >> N >> M >> Y >> X >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	int y = Y, x = X;
	int ny, nx;
	int cmd;

	for (int i = 0; i < K; i++) {
		cin >> cmd;
		ny = y + dy[cmd];
		nx = x + dx[cmd];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;

		//회전
		func(cmd);

		if (map[ny][nx] == 0)
			map[ny][nx] = cube[2];
		else {
			cube[2] = map[ny][nx];
			map[ny][nx] = 0;
		}

		y = ny;
		x = nx;

		cout << cube[0] << endl;
	}
	return 0;
}