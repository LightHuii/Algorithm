#include<iostream>
#include<algorithm>
#include<memory.h>
#include<math.h>
#include<queue>
using namespace std;

#define MAX 50
int N, L, R;
int map[MAX][MAX];
int visit[MAX][MAX];
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

//bfs를 할 수 있는 좌표인지 판단
bool judge(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		int cmp = abs(map[y][x] - map[ny][nx]);
		if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
		if (cmp >= L && cmp <= R)return true;
	}
	return false;
}

//sum/n 리턴
int bfs(int y, int x, int num) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));
	int n = 0;
	int sum = 0;

	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		visit[y][x] = num;
		n++;
		sum += map[y][x];

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			int cmp = abs(map[y][x] - map[ny][nx]);

			if (visit[ny][nx] != 0 || ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
			if (cmp >= L && cmp <= R) {
				visit[ny][nx] = num;
				q.push(make_pair(ny, nx));
			}
		}
	}

	return sum / n;
}

//값 넣기만하는 함수
void pop_move(int y, int x, int val, int num) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == num)
				map[i][j] = val;
		}
	}
}

int main() {
	int move = 0;
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	bool flag = false;	//한 번이라도 실행됐는지 확인
	int num, tmp;
	while (1) {
		//초기화
		num = 1;
		memset(visit, 0, sizeof(visit));
		flag = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visit[i][j] != 0 || !judge(i, j))continue;
				tmp = bfs(i, j, num);
				pop_move(i, j, tmp, num);
				num++;
				flag = true;
			}
		}
		//한 번도 실행되지 않았다면 끝내기
		if (!flag)break;
		move++;
	}

	cout << move << endl;

	return 0;
}