#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 100
int N, L, T;
int map[MAX][MAX] = { 0, };
bool visited[MAX][MAX];	//경사로 기록

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {

		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));
		int cnt = 0;

		cin >> N >> L;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		//세로
		for (int j = 0; j < N; j++) {
			bool judge = false;
			for (int i = 0; i < N - 1; i++) {

				if (map[i][j] - map[i + 1][j] == 1) {
					int y;
					bool flag = false;
					for (y = i + 1; y <= i + L; y++) {
						if (y >= N || map[i + 1][j] != map[y][j]) {
							flag = true;
							judge = true;
							break;
						}
						visited[y][j] = true;
					}
					y--;
					i = y - 1;
				}
				else if (map[i][j] - map[i + 1][j] == -1) {
					int y;
					for (y = i; y > i - L; y--) {
						if (y < 0 || visited[y][j] || map[i][j] != map[y][j]) {
							judge = true;
							break;
						}
						visited[y][j] = true;
					}
				}
				else if (map[i][j] - map[i + 1][j] > 1 || map[i][j] - map[i + 1][j] < -1)
					judge = true;
			}

			if (!judge)
				cnt++;
		}

		memset(visited, false, sizeof(visited));
		//가로
		for (int i = 0; i < N; i++) {
			bool judge = false;
			for (int j = 0; j < N - 1; j++) {

				if (map[i][j] - map[i][j + 1] == 1) {
					int x;
					bool flag = false;
					for (x = j + 1; x <= j + L; x++) {
						if (x >= N || map[i][j + 1] != map[i][x]) {
							flag = true;
							judge = true;
							break;
						}
						visited[i][x] = true;
					}
					x--;
					j = x - 1;
				}
				else if (map[i][j] - map[i][j + 1] == -1) {
					int x;
					for (x = j; x > j - L; x--) {
						if (x < 0 || visited[i][x] || map[i][j] != map[i][x]) {
							judge = true;
							break;
						}
						visited[i][x] = true;
					}
				}
				else if (map[i][j] - map[i][j + 1] > 1 || map[i][j] - map[i][j + 1] < -1)
					judge = true;
			}
			if (!judge)
				cnt++;
		}

		cout << '#' << T - Ttmp << ' ' << cnt << endl;
	}
	return 0;
}