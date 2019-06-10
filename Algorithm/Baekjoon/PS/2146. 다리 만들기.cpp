#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 100
int N;
int map_origin[MAX][MAX] = { 0, };	//입력된 맵
int map[MAX][MAX] = { 0, };			//넘버링된 맵
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
bool visited[MAX][MAX];		//넘버링할 때 사용
int rst = INT32_MAX;		//결과

//섬에 번호를 매긴다
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

//테두리부터 bfs
void bfs(int y, int x, int n) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	bool visit[MAX][MAX];
	memset(visit, false, sizeof(visit));
	visit[y][x] = true;

	int cycle = 0;	//사이클 횟수

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			y = q.front().first;
			x = q.front().second;
			q.pop();

			if (map[y][x] != 0 && map[y][x] != n) {
				rst = min(rst, cycle);
				return;	//어차피 같은 사이클 내에서는 같기 때문에 바로 리턴 가능
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				
				//아직 들리지 않았고, 바다 또는 다른 섬일 때
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

	//맵 넘버링
	int num = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map_origin[i][j] == 1 && !visited[i][j]) {
				dfs(i, j, num);
				num++;
			}
		}
	}

	//테두리 판단, bfs
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] != 0)continue;
			bool flag = false;
			int n;	//섬 번호

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				
				if (map[ny][nx] != 0) {
					flag = true;		//하나라도 섬이 옆에 있으면 현재를 테두리로 판단
					n = map[ny][nx];
					break;
				}
			}
			//테두리라면, bfs
			if (flag)
				bfs(y, x, n);
		}
	}

	cout << rst << endl;

	return 0;
}