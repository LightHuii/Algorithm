#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 100
int N;
int map_origin[MAX][MAX] = { 0, };	//�Էµ� ��
int map[MAX][MAX] = { 0, };			//�ѹ����� ��
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
bool visited[MAX][MAX];		//�ѹ����� �� ���
int rst = INT32_MAX;		//���

//���� ��ȣ�� �ű��
void dfs(int y, int x, int n) {
	map[y][x] = n;
	visited[y][x] = true;

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
		if (map_origin[ny][nx] == 1 && !visited[ny][nx])
			dfs(ny, nx, n);
	}
}

//�׵θ����� bfs
void bfs(int y, int x, int n) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	bool visit[MAX][MAX];
	memset(visit, false, sizeof(visit));
	visit[y][x] = true;

	int cycle = 0;	//����Ŭ Ƚ��

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			y = q.front().first;
			x = q.front().second;
			q.pop();

			if (map[y][x] != 0 && map[y][x] != n) {
				rst = min(rst, cycle);
				return;	//������ ���� ����Ŭ �������� ���� ������ �ٷ� ���� ����
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				
				//���� �鸮�� �ʾҰ�, �ٴ� �Ǵ� �ٸ� ���� ��
				if (map[ny][nx] != n && !visit[ny][nx]) {
					visit[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
		cycle++;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map_origin[i][j];

	//�� �ѹ���
	int num = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map_origin[i][j] == 1 && !visited[i][j]) {
				dfs(i, j, num);
				num++;
			}
		}
	}

	//�׵θ� �Ǵ�, bfs
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] != 0)continue;
			bool flag = false;
			int n;	//�� ��ȣ

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				
				if (map[ny][nx] != 0) {
					flag = true;		//�ϳ��� ���� ���� ������ ���縦 �׵θ��� �Ǵ�
					n = map[ny][nx];
					break;
				}
			}
			//�׵θ����, bfs
			if (flag)
				bfs(y, x, n);
		}
	}

	cout << rst << endl;

	return 0;
}