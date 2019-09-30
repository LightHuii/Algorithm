#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory.h>
#include <tuple>
using namespace std;

/*
주의할 점
1. 죄수끼리는 반드시 만날 수 있는 입력이 주어진다.
2. 두 죄수의 탈출 루트 또한 무조건 존재한다.

map을 한 칸씩 확장하여 (0,0), 죄수1, 죄수2 세 지점에서 BFS를 실행한다.
각 BFS결과를 모두 더한 뒤(문 좌표의 경우 -2한다. -> 3번 열었기 때문에)
최소 값이 답이다.
그 이유는 두 죄수가 만나는 최소 비용 + 나가는 경로의 최소 비용을 모두 만족해야 하기 때문이다.
즉, 3번의 BFS를 통해 만나는 접점이 곧 최소비용 좌표다.
*/

#define MAX 102
int h, w, T;
char map[MAX][MAX];
int cost[3][MAX][MAX];
int rst[MAX][MAX];
vector<pair<int, int>>person;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

void bfs(int y, int x, int n) {
	//지나간 길(cost)를 -1로 초기화
	for (int i = 0; i < h + 2; i++)
		for (int j = 0; j < w + 2; j++)
			cost[n][i][j] = -1;

	queue<tuple<int, int, int>>q;
	q.push(make_tuple(y, x, 0));	//좌표, 문을 연 횟수
	cost[n][y][x] = 0;				//시작점은 0으로 시작한다.

	while (!q.empty()) {
		y = get<0>(q.front());
		x = get<1>(q.front());
		int cnt = get<2>(q.front());
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= h + 2 || nx < 0 || nx >= w + 2)continue;
			if (map[ny][nx] != '*') {
				//그냥 지나갈 수 있는 곳일 때
				if (map[ny][nx] == '.' || map[ny][nx] == '$') {
					//처음 가는 길이거나 더 적은 비용으로 갈 수 있는 길일 경우
					if (cost[n][ny][nx] == -1 || cost[n][ny][nx] > cnt) {
						cost[n][ny][nx] = cnt;
						q.push(make_tuple(ny, nx, cnt));
					}
				}
				//문일 때
				else if (map[ny][nx] == '#') {
					//처음 가는 길이거나 더 적은 비용으로 갈 수 있는 길일 경우
					if (cost[n][ny][nx] == -1 || cost[n][ny][nx] > cnt + 1) {
						cost[n][ny][nx] = cnt + 1;
						q.push(make_tuple(ny, nx, cnt + 1));
					}
				}
			}
		}
	}
}

int main(void)
{
	cin >> T;
	while (T--) {
		//초기화
		person.clear();
		memset(cost, 0, sizeof(cost));

		cin >> h >> w;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i + 1][j + 1];

				//죄수의 좌표 저장
				if (map[i + 1][j + 1] == '$')
					person.push_back(make_pair(i + 1, j + 1));
			}
		}
		//좌표를 확장하기 때문에 빈 공간으로 채워준다
		for (int i = 0; i < h + 2; i++) map[i][0] = '.';
		for (int i = 0; i < h + 2; i++) map[i][w + 1] = '.';
		for (int j = 0; j < w + 2; j++) map[0][j] = '.';
		for (int j = 0; j < w + 2; j++) map[h + 1][j] = '.';

		//각각 BFS
		bfs(0, 0, 0);
		bfs(person[0].first, person[0].second, 1);
		bfs(person[1].first, person[1].second, 2);

		//모든 좌표에 대한 cost를 더해준다
		int result = 10000;
		for (int i = 0; i < h + 2; i++) {
			for (int j = 0; j < w + 2; j++) {
				//문의 경우 한 번만 열어야 하기 때문에 2를 빼준다
				if (map[i][j] == '#')
					rst[i][j] = cost[0][i][j] + cost[1][i][j] + cost[2][i][j] - 2;
				else
					rst[i][j] = cost[0][i][j] + cost[1][i][j] + cost[2][i][j];
				//지나간 길에 대한 최소 값
				if (rst[i][j] >= 0)
					result = min(result, rst[i][j]);
			}
		}
		
		cout << result << endl;
	}

	return 0;
}