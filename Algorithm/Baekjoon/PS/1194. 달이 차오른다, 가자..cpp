#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

//큐에 들어갈 자료형
typedef struct a {
	int y, x, move;
	char info;
}Cell;

#define MAX 50
#define gap 'A'-'a'
int N, M;
char map[MAX][MAX];
bool visited[64][MAX][MAX];
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

int bfs(int y, int x) {
	queue<Cell>q;
	Cell t = { y, x, 0, 0 };	//좌표, 이동 수, 열쇠 유무
	q.push(t);
	map[y][x] = '.';

	int result = INT32_MAX;
	while (!q.empty()) {
		y = q.front().y;
		x = q.front().x;	//좌표
		int cnt = q.front().move;		//이동 횟수
		char info = q.front().info;		//획득한 열쇠 정보
		visited[(int)info][y][x] = true;
		q.pop();
		
		if (result <= cnt)continue;
		if (map[y][x] == '1')
			result = min(result, cnt);

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			char tmp = map[ny][nx];
			char ninfo = info | (1 << (tmp - 'a'));

			if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;
			if (map[ny][nx] == '#')continue;

			//열쇠
			if (map[ny][nx] >= 'a' && map[ny][nx] <= 'f' && !visited[(int)ninfo][ny][nx]) {
				visited[(int)ninfo][ny][nx] = true;
				Cell cell = { ny, nx, cnt + 1, info | (1 << (tmp - 'a')) };
				q.push(cell);
				//map[ny][nx] = '.';
			}
			//문
			else if (map[ny][nx] >= 'A' && map[ny][nx] <= 'F' && !visited[(int)info][ny][nx]) {
				if (info & (1 << (tmp + gap - 'a'))) {
					visited[(int)info][ny][nx] = true;
					Cell cell = { ny, nx, cnt + 1, info };
					q.push(cell);
				}
			}
			//길 or 출구
			else if(!visited[(int)info][ny][nx]){
				visited[(int)info][ny][nx] = true;
				Cell cell = { ny, nx, cnt + 1, info };
				q.push(cell);
			}
		}
	}

	if (result == INT32_MAX)
		return -1;
	else
		return result;
}

int main()
{
	int sy = 0, sx = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			//시작점 좌표 저장
			if (map[i][j] == '0') {
				sy = i;
				sx = j;
			}
		}
	}

	cout << bfs(sy, sx) << endl;

	return 0;
}