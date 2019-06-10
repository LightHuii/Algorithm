#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>
using namespace std;

//바이러스
#define MAX 50
int map[MAX][MAX];
int visited[MAX][MAX] = { 0, };
vector<pair<int, int>>virus_locate;
bool selected[10];
int rst = INT32_MAX;	//최소값 저장
int N, M;
int vicnt = 0;	//바이러스를 놓을 수 있는 지점의 개수 == virus_locate.size()
int zero_num = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };


int bfs() {
	queue<pair<int, int>>q;
	for (int i = 0; i < vicnt; i++) {
		if (selected[i]) {
			q.push(virus_locate[i]);
			visited[virus_locate[i].first][virus_locate[i].second] = 1;
		}
	}

	int t = 0;
	int tzero = zero_num;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N || map[ny][nx] == 1)continue;
				if (visited[ny][nx] == 0) {
					visited[ny][nx] = visited[y][x] + 1;
					t = max(t, visited[ny][nx]);
					q.push(make_pair(ny, nx));
					if (map[ny][nx] == 0) tzero--;
				}
			}
		}
		if (tzero == 0) {
			return t - 1;
		}
	}

	return -1;
}

void dfs(int cnt, int idx) {
	if (cnt == M) {
		//실행
		int tmp = bfs();
		if (tmp != -1)
			rst = min(rst, tmp);

		memset(visited, 0, sizeof(visited));
		return;
	}
	if (idx >= vicnt)return;


	if (!selected[idx]) {
		selected[idx] = true;
		dfs(cnt + 1, idx + 1);
		selected[idx] = false;
	}
	dfs(cnt, idx + 1);
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus_locate.push_back(make_pair(i, j));
				vicnt++;
			}
			else if (map[i][j] == 0)
				zero_num++;
		}
	}

	if (zero_num > 0)
		dfs(0, 0);

	if (rst == INT32_MAX) {
		if (zero_num == 0)
			cout << 0 << endl;
		else
			cout << -1 << endl;
	}
	else
		cout << rst << endl;
	return 0;
}