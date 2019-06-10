#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<memory.h>
using namespace std;

char map[12][6];
char tmp[12][6];
int rst = 0;	//연쇄 횟수
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
bool visited[12][6];

int bfs(int y, int x, char c) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	int cnt = 0;

	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();

		//일단 없애고 횟수 증가
		map[y][x] = '.';
		visited[y][x] = true;
		cnt++;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= 12 || nx < 0 || nx >= 6)continue;
			if (!visited[ny][nx] && map[ny][nx] == c) {
				visited[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
		}
	}
	return cnt;
}

void arrange(int x) {
	stack<char>st;

	for (int y = 0; y < 12; y++) {
		if (map[y][x] != '.')
			st.push(map[y][x]);
		map[y][x] = '.';
	}

	int size = st.size();
	for (int i = 0; i < size; i++) {
		map[11 - i][x] = st.top();
		st.pop();
	}
}

int main() {
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 6; j++)
			cin >> map[i][j];


	//bfs가 진행되지 않을 때까지
	while (1) {
		int judge = 0;	//cnt 최대값
		int cnt = 0;

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] != '.') {
					memset(visited, false, sizeof(visited));
					memcpy(tmp, map, sizeof(map));

					cnt = bfs(i, j, map[i][j]);
					judge = max(cnt, judge);

					if (cnt < 4)
						memcpy(map, tmp, sizeof(map));
				}
			}
		}

		//한 번도 연쇄가 일어나지 않는다면
		if (judge < 4)break;
		else rst++;

		for (int i = 0; i < 6; i++)
			arrange(i);
	}

	cout << rst << endl;

	return 0;
}
​