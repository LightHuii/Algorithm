#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 17
int map[MAX][MAX];
int rst = 0, N;

void dfs(int y, int x, int dir) {
	if (y == N && x == N) {
		rst++;
		return;
	}

	//가로일 때
	if (dir == 0) {
		if (x + 1 <= N && map[y][x + 1] == 0)
			dfs(y, x + 1, 0);
		if (x + 1 <= N && y + 1 <= N && map[y][x + 1] == 0 && map[y + 1][x] == 0 && map[y + 1][x + 1] == 0)
			dfs(y + 1, x + 1, 2);
	}
	//세로일 때
	else if (dir == 1) {
		if (y + 1 <= N && map[y + 1][x] == 0)
			dfs(y + 1, x, 1);
		if (x + 1 <= N && y + 1 <= N && map[y][x + 1] == 0 && map[y + 1][x] == 0 && map[y + 1][x + 1] == 0)
			dfs(y + 1, x + 1, 2);
	}
	//대각선일 때
	else if (dir == 2) {
		if (x + 1 <= N && map[y][x + 1] == 0)
			dfs(y, x + 1, 0);
		if (y + 1 <= N && map[y + 1][x] == 0)
			dfs(y + 1, x, 1);
		if (x + 1 <= N && y + 1 <= N && map[y][x + 1] == 0 && map[y + 1][x] == 0 && map[y + 1][x + 1] == 0)
			dfs(y + 1, x + 1, 2);
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];

	dfs(1, 2, 0);

	cout << rst << endl;

	return 0;
}