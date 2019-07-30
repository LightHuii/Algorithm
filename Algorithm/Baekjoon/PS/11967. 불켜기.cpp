#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 101
vector<pair<int, int>> adj[MAX][MAX];
int N, M;
bool room[MAX][MAX];
bool visited[MAX][MAX];
int rst = 1;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

bool bfs() {
	queue<pair<int, int>>q;
	q.push(make_pair(1, 1));

	bool ret = false;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			visited[y][x] = true;

			//���翡�� ų �� �ִ� ���� ���� Ű��
			for (int i = 0; i < (int)adj[y][x].size(); i++) {
				int ny = adj[y][x][i].first;
				int nx = adj[y][x][i].second;
				if (!room[ny][nx]) {
					room[ny][nx] = true;
					rst++;
					ret = true;
				}
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny <= 0 || ny > N || nx <= 0 || nx > N)continue;
				if (room[ny][nx] && !visited[ny][nx]) {
					visited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
	}
	return ret;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int x, y, a, b;
		cin >> y >> x >> b >> a;

		adj[y][x].push_back(make_pair(b, a));
	}

	room[1][1] = true;

	//���̻� ���� ������ ���� ������ 1, 1���� ���� ����
	while (1) {
		bool tmp = bfs();
		if (!tmp)break;
		memset(visited, false, sizeof(visited));
	}
	cout << rst << endl;

	return 0;
}