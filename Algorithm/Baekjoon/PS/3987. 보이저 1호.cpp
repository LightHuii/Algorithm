#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 501
int N, M;
char map[MAX][MAX];
int visited[MAX][MAX] = { 0, };
int sy, sx;		//시작점
char dir[4] = { 'U', 'R', 'D', 'L' };
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

char bigger(int a, int b) {
	if (a >= b)return b;
	else return a;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];

	cin >> sy >> sx;
	int rst_t = 0;
	int rst_d = -1;
	bool flag = false;

	for (int i = 0; i < 4; i++) {
		//초기화
		memset(visited, false, sizeof(visited));
		int y = sy;
		int x = sx;
		int d = i;

		int t = 0;

		if (flag)break;

		while (1) {
			//cout << "y, x: " << y << ", " << x << endl;
			//cout << "d, t: " << d << ", " << t << endl<<endl;

			//현재 시그널 위치 판단
			if (y <= 0 || y > N || x <= 0 || x > M)break;
			else if (map[y][x] == 'C')break;
			else if (map[y][x] == '/') {
				switch (d)
				{
				case 0: d = 1; break;
				case 1: d = 0; break;
				case 2: d = 3; break;
				case 3: d = 2; break;
				default:
					break;
				}
			}
			else if (map[y][x] == '\\') {
				switch (d)
				{
				case 0: d = 3; break;
				case 1: d = 2; break;
				case 2: d = 1; break;
				case 3: d = 0; break;
				default:
					break;
				}
			}
			else if (visited[y][x] > 1) {
				flag = true;
				rst_d = bigger(i, rst_d);
				break;
			}

			//표시 및 다음으로 이동
			visited[y][x]++;
			int ny = y + dy[d];
			int nx = x + dx[d];

			//시간 증가
			t++;

			y = ny;
			x = nx;
		}

		if (t > rst_t) {
			rst_t = t;
			rst_d = i;
		}
		else if (t == rst_t) {
			rst_d = bigger(i, rst_d);
		}
	}

	if (!flag)
		cout << dir[rst_d] << endl << rst_t << endl;
	else
		cout << dir[rst_d] << endl << "Voyager" << endl;

	return 0;
}