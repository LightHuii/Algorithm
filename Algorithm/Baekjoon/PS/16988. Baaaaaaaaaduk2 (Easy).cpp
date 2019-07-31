#include<iostream>
#include<algorithm>
#include<memory.h>
#include<queue>
using namespace std;

#define MAX 20
int N, M;
int map[MAX][MAX];
bool visited[MAX][MAX];
int rst = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

//��� ���� ������ ������ 0, ������ ���� ���� ����
int bfs(int y, int x) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	int stone_cnt = 0;	//��� ���� ����
	bool flag = false;
	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		stone_cnt++;
		visited[y][x] = true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;
			if (!visited[ny][nx] && map[ny][nx] == 2) {
				visited[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
			//�ֺ��� ����ִ� ���� �ִٸ� ������ üũ �� 0����
			if (map[ny][nx] == 0)
				flag = true;
		}
	}

	if (!flag)
		return stone_cnt;
	else
		return 0;
}

void dfs(int cnt, int y, int x) {
	if (cnt >= 2) {
		memset(visited, false, sizeof(visited));

		int tmp = 0;
		//��� ���� Ž���ϸ� ���� ���� ���� ����
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (!visited[i][j] && map[i][j] == 2)
					tmp += bfs(i, j);
			}
		}
		rst = max(rst, tmp);
		return;
	}
	if (y >= N)return;

	//���� ��ǥ
	int nx = x + 1;
	int ny = y;
	if (nx >= M) {
		nx = 0;
		ny++;
	}

	if (map[y][x] == 0) {
		map[y][x] = 1;
		dfs(cnt + 1, ny, nx);
		map[y][x] = 0;
	}
	dfs(cnt, ny, nx);
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	dfs(0, 0, 0);
	cout << rst << endl;

	return 0;
}