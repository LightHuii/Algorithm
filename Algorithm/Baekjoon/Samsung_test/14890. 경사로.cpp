#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 100
int N, L;
int map[MAX][MAX];
bool visited[MAX][MAX];

int main() {
	int rst = 0;
	cin >> N >> L;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	//행 단위
	for (int y = 0; y < N; y++) {
		bool flag = false;

		for (int x = 0; x < N - 1; x++) {

			if (map[y][x] - map[y][x + 1] == 1) {
				//오른 쪽으로 경사로를 둠
				for (int i = 1; i <= L; i++) {
					if (x + i >= N || map[y][x + i] != map[y][x + 1]) {	//경사로를 놓지 못하는 조건
						flag = true;
						break;
					}
					visited[y][x + i] = true;	//경사로
				}
				if (flag)break;

				//경사로를 다 놓은 상태
				x += L - 1;	//다음 차례에 x+L+1이 된다.
			}
			else if (map[y][x] - map[y][x + 1] == -1) {
				//왼 쪽으로 경사로를 둠
				for (int i = 0; i < L; i++) {
					if (visited[y][x - i] || x - i < 0 || map[y][x - i] != map[y][x]) {	//경사로를 놓지 못 하는 조건
						flag = true;
						break;
					}
					visited[y][x - i] = true;	//경사로
				}
				if (flag)break;
				//경사로를 다 놓은 상태
				//다음 차례에 알아서 증가한다.
			}
			else if (map[y][x] - map[y][x + 1] >= 2 || map[y][x] - map[y][x + 1] <= -2) {
				flag = true;
				break;
			}
		}
		if (flag)continue;	//실패하면 카운트하지 않는다.
		rst++;
	}

	memset(visited, false, sizeof(visited));

	//열 단위
	for (int x = 0; x < N; x++) {
		bool flag = false;

		for (int y = 0; y < N - 1; y++) {

			if (map[y][x] - map[y + 1][x] == 1) {
				//아래쪽으로 경사로를 둠
				for (int i = 1; i <= L; i++) {
					if (y + i >= N || map[y + i][x] != map[y + 1][x]) {	//경사로를 놓지 못하는 조건
						flag = true;
						break;
					}
					visited[y + i][x] = true;	//경사로
				}
				if (flag)break;

				//경사로를 다 놓은 상태
				y += L - 1;	//다음 차례에 y+L+1이 된다.
			}
			else if (map[y][x] - map[y + 1][x] == -1) {
				//왼 쪽으로 경사로를 둠
				for (int i = 0; i < L; i++) {
					if (visited[y - i][x] || y - i < 0 || map[y - i][x] != map[y][x]) {	//경사로를 놓지 못 하는 조건
						flag = true;
						break;
					}
					visited[y - i][x] = true;	//경사로
				}
				if (flag)break;
				//경사로를 다 놓은 상태
				//다음 차례에 알아서 증가한다.
			}
			else if (map[y][x] - map[y + 1][x] >= 2 || map[y][x] - map[y + 1][x] <= -2) {
				flag = true;
				break;
			}
		}
		if (flag)continue;	//실패하면 카운트하지 않는다.
		rst++;
	}

	cout << rst << endl;
	return 0;
}