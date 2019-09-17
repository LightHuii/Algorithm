#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 10
int map[MAX][MAX];
int N;
int rst = INT32_MAX;
bool visited[MAX][MAX];
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

//현재 좌표에 씨앗을 놓을 수 있는지 확인
bool can_select(int y, int x) {
	if (y <= 0 || y >= N - 1 || x <= 0 || x >= N - 1)return false;

	//꽃잎이 겹치면 false
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (visited[ny][nx])return false;
	}

	return true;
}

//cnt: 현재까지 선택한 좌표 수, cost: 선택된 모든 스팟의 비용
void dfs(int cnt, int y, int x, int cost) {
	if (rst <= cost)return;
	if (cnt >= 3) {
		rst = min(rst, cost);
		return;
	}
	if (y >= N)return;

	int ny = y, nx = x + 1;
	int ncost = cost;
	if (nx >= N) {
		nx = 0;
		ny++;
	}

	//선택할 수 있다면
	if (can_select(y, x)) {
		ncost += map[y][x];
		visited[y][x] = true;
		for (int i = 0; i < 4; i++) {
			int nny = y + dy[i];
			int nnx = x + dx[i];
			ncost += map[nny][nnx];
			visited[nny][nnx] = true;
		}

		dfs(cnt + 1, ny, nx, ncost);

		//복구
		visited[y][x] = false;
		for (int i = 0; i < 4; i++) {
			int nny = y + dy[i];
			int nnx = x + dx[i];
			visited[nny][nnx] = false;
		}
	}

	//선택하지 않고 지나가는 경우
	dfs(cnt, ny, nx, cost);
}


int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	dfs(0, 0, 0, 0);
	cout << rst << endl;

	return 0;
}