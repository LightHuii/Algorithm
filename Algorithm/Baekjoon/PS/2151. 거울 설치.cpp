#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef struct a {
	int y, x, dir, cnt;		//좌표, 방향, 지금까지 거울 수 
}info;
#define MAX 50
int N;
char map[MAX][MAX];
vector<pair<int, int>>door;
int dy[] = { -1,0,1,0 };		//북동남서
int dx[] = { 0,1,0,-1 };
//들렀던 거울'만' 체크한다. 경로까지 체크하면 다른 경로에 의해 최소 경로의 진행을 막을 수도 있다.
//또한, visited에 들어가는 값은 현재 경로에서 사용된 거울의 수로, 더 적은 거울을 사용하는 경로는 지나갈 수 있도록 했다.
int visited[MAX][MAX] = { 0, };

//처음 시작에서부터 !일 경우 거울을 놓고 이동해보면서, 최소 거울 수를 리턴
int bfs() {
	queue<info>q;
	for (int i = 0; i < 4; i++) {
		info tmp = { door[0].first, door[0].second, i, 0 };		//초기 값
		q.push(tmp);
	}

	int rst = INT32_MAX;		//최소 거울 수
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int dir = q.front().dir;
		int cnt = q.front().cnt;
		q.pop();

		if (y < 0 || y >= N || x < 0 || x >= N)continue;	//범위를 벗어나면 다음 차례

		//도착한다면
		if (y == door[1].first && x == door[1].second) {
			rst = min(rst, cnt);
			continue;		//더 늦게 더 적은 거울을 사용하는 경우가 있으므로 리턴하지 않는다.
		}

		//현재 좌표의 경우에 따라 다음 좌표 결정
		int ny, nx, nd, nc;
		//현재가 빈 칸이거나 목적지일 경우
		if (map[y][x] == '.' || map[y][x] == '#') {
			//방향은 그대로 직진
			ny = y + dy[dir];
			nx = x + dx[dir];
			nd = dir;
			nc = cnt;
			if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
			//다음 순서 확인
			//아직 들지 않은 !이거나, 더 적은 거울로 갈 수 있는 경로일 때
			if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] > cnt + 1)) {
				if(map[ny][nx] == '!')		//다음이 !일 경우만 체크해준다.
					visited[ny][nx] = cnt + 1;
				info tmp = { ny, nx, nd, nc };
				q.push(tmp);
			}
		}
		//현재 !라면
		else if (map[y][x] == '!') {
			//처음은 무조건 #이므로 visit을 표시 안 해줘도 된다.
			//또한, 현재 차례에만 넣는 것이 아니라
			//다음 차례를 미리 확인하여 큐에 넣지 않도록 하여 메모리 초과를 막을 수 있다.

			//거울을 무시하고 직진하거나, 양 옆으로 가는 경로만 고려한다.
			for (int i = 0; i < 4; i++) {
				if (i == 2)continue;
				nd = (dir + i) % 4;
				ny = y + dy[nd];
				nx = x + dx[nd];
				if (i != 0)
					nc = cnt + 1;	//거울을 사용할 경우 카운트
				else
					nc = cnt;	//직진할 경우 카운트하지 않는다.
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;

				//마찬가지로, 더 적은 거울을 사용할 수 있는 경로일 경우 체크하여 지나갈 수 있도록 한다.
				if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] > cnt + 1)) {
					if (map[ny][nx] == '!')
						visited[ny][nx] = cnt + 1;
					info tmp = { ny, nx, nd, nc };
					q.push(tmp);
				}
			}
		}
	}

	return rst;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == '#')
				door.push_back(make_pair(i, j));	//문 좌표 저장
		}
	}

	int rst = 0;
	rst = bfs();
	cout << rst << endl;
}