#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 10
int map[MAX][MAX];
bool visited[MAX][MAX];
int block_cnt = 0;
int rst = INT32_MAX;
int scale[6] = { 0, 5, 5, 5, 5, 5 };

bool isCover(int y, int x, int s) {
	for (int i = y; i < y + s; i++)
		for (int j = x; j < x + s; j++)
			if (visited[i][j] || map[i][j] == 0)return false;
	return true;
}

void cover(int y, int x, int s) {
	for (int i = y; i < y + s; i++)
		for (int j = x; j < x + s; j++)
			visited[i][j] = true;
}

void discover(int y, int x, int s) {
	for (int i = y; i < y + s; i++)
		for (int j = x; j < x + s; j++)
			visited[i][j] = false;
}

void dfs(int y, int x, int cnt, int area) {
	if (cnt >= rst)return;
	if (area == block_cnt) {
		rst = min(rst, cnt);
		return;
	}

	//시작 점 찾기
	while (1) {
		if (map[y][x] == 1 && !visited[y][x])
			break;
		x++;
		if (x == 10) {
			x = 0;
			y++;
			if (y >= MAX)return;
		}
	}

	for (int s = 5; s >= 1; s--) {
		if (isCover(y, x, s) && scale[s] > 0) {
			//덮기
			scale[s] -= 1;
			cover(y, x, s);
			dfs(y, x, cnt + 1, area + s*s);

			scale[s] += 1;
			discover(y, x, s);
		}
	}
}

int main() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) block_cnt++;
		}
	}

	if (block_cnt == 0)
		cout << 0 << endl;
	else {
		dfs(0, 0, 0, 0);
		if (rst == INT32_MAX)
			cout << -1 << endl;
		else
			cout << rst << endl;
	}

	return 0;
}