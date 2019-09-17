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

//���� ��ǥ�� ������ ���� �� �ִ��� Ȯ��
bool can_select(int y, int x) {
	if (y <= 0 || y >= N - 1 || x <= 0 || x >= N - 1)return false;

	//������ ��ġ�� false
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (visited[ny][nx])return false;
	}

	return true;
}

//cnt: ������� ������ ��ǥ ��, cost: ���õ� ��� ������ ���
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

	//������ �� �ִٸ�
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

		//����
		visited[y][x] = false;
		for (int i = 0; i < 4; i++) {
			int nny = y + dy[i];
			int nnx = x + dx[i];
			visited[nny][nnx] = false;
		}
	}

	//�������� �ʰ� �������� ���
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