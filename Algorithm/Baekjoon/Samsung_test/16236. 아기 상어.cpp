#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
#include<queue>
using namespace std;

#define MAX 20
int map[MAX][MAX];
bool visited[MAX][MAX];
int N, M;
int weight = 2;
int shark_time = 0;
int shark_cnt = 0;
int Y, X;	//상어의 좌표
int dy[] = { -1,0,0,1 };	//북, 서, 동, 남
int dx[] = { 0,-1,1,0 };


bool bfs() {
	queue<pair<int, int>>q;
	q.push(make_pair(Y, X));

	int cnt = 0;
	while (!q.empty()) {
		int size = q.size();

		//벡터에 옮긴 후, y에 대해 오름차순으로 정렬
		vector<pair<int, int>>v;
		for (int i = 0; i < size; i++) {
			v.push_back(q.front());
			q.pop();
		}
		sort(v.begin(), v.end());

		int idx = 0;
		while (size--) {
			int y = v[idx].first;
			int x = v[idx].second;
			visited[y][x] = true;
			idx++;

			//먹이 가능
			if (map[y][x] >= 1 && map[y][x] < weight && map[y][x] <= 6) {
				shark_cnt++;		//상어가 먹은 횟수 증가
									//크기 증가
				if (shark_cnt >= weight) {
					weight++;
					shark_cnt = 0;
				}
				shark_time += cnt;	//상어의 이동 거리

									//상어 좌표 이동
				map[Y][X] = 0;
				Y = y;
				X = x;
				map[Y][X] = 9;

				return true;
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N || map[ny][nx]>weight)continue;
				if (!visited[ny][nx]) {
					visited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
		cnt++;
	}

	//먹이를 먹지 못 한 경우
	return false;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				Y = i;
				X = j;
			}
		}
	}

	bool judge;
	while (1) {
		//visit 초기화
		memset(visited, false, sizeof(visited));

		//먹이를 한 번이라도 먹었다면 true, 아니라면 false
		judge = bfs();
		if (!judge)
			break;
	}

	cout << shark_time << endl;

	return 0;
}
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 20
int map[MAX][MAX];
bool visited[MAX][MAX];
int N;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

typedef struct _node {
	int y, x, size, ate;
}shark;
shark s;

int bfs() {
	queue<pair<int, int>>q;
	q.push(make_pair(s.y, s.x));
	vector<pair<int, int>>v;

	int t = 0;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			visited[y][x] = true;

			//자신보다 작은 물고기라면
			if (map[y][x] >= 1 && map[y][x] <= 6 && map[y][x] < s.size) {
				map[y][x] = 0;
				s.ate++;
				s.y = y;
				s.x = x;
				if (s.ate == s.size) {
					s.ate = 0;
					s.size++;
				}
				return t;
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
				if (map[ny][nx] <= s.size && !visited[ny][nx]) {
					visited[ny][nx] = true;
					v.push_back(make_pair(ny, nx));
				}
			}
		}
		t++;

		sort(v.begin(), v.end());
		size = v.size();
		for (int i = 0; i < size; i++)
			q.push(v[i]);
		v.clear();
	}
	return -1;
}

int main() {
	int cnt = 0;
	int rst = 0;

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				s.y = i;
				s.x = j;
				map[i][j] = 0;
			}
		}
	}
	s.ate = 0;
	s.size = 2;

	while (1) {
		memset(visited, false, sizeof(visited));
		cnt = bfs();

		if (cnt == -1)break;
		rst += cnt;
	}

	cout << rst << endl;
	return 0;
}