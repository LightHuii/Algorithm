#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 1500
int R, C;
char map[MAX][MAX];
int melt_day[MAX][MAX] = { 0, };	//얼음이 녹는 날짜를 기록
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
pair<int, int> swan[2];	//백조 좌표
int visited[MAX][MAX];

//t까지 백조가 이동할 수 있다. 
bool bfs(int t) {
	queue<pair<int, int>>q;
	q.push(swan[0]);	//백조부터 시작

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		visited[y][x] = t;		//visited를 초기화하지 않고 사용
		q.pop();

		//다른 백조 찾으면 true
		if (y == swan[1].first && x == swan[1].second)
			return true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= R || nx < 0 || nx >= C)continue;

			//물이거나, t번째에 이동할 수 있는 얼음일 경우
			if (map[ny][nx] == '.' || (map[ny][nx] == 'X' && melt_day[ny][nx] <= t)) {
				if (visited[ny][nx] != t) {
					visited[ny][nx] = t;		//방문 표시
					q.push(make_pair(ny, nx));
				}
			}
		}
	}

	return false;
}

//0 ~ t번째 날 중 최소로 갈 수 있는 날을 찾는 이분탐색
int bsearch(int s, int e) {
	int start = s, end = e;
	int mid = (start + end) / 2;
		
	while (start <= end) {
		mid = (start + end) / 2;
		if (start == end)break;		//start == end == mid일 때 탐색 완료

		//백조가 서로 만날 수 있을 때
		if (bfs(mid))
			end = mid;	//mid가 답이 될 수 있으므로
		//서로 못 만날 때
		else
			start = mid + 1;	//mid는 답이 될 수 없으므로
	}

	return mid;
}

int main()
{
	cin >> R >> C;

	//입력
	int index = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'L') {
				map[i][j] = '.';
				swan[index++] = make_pair(i, j);
			}
			visited[i][j] = -1;
		}
	}

	//전처리
	queue<pair<int, int>>q[2];	//큐 두 개를 번갈아 가며 사용
	bool idx = 0;

	//1일차에 녹는 얼음의 좌표를 표시하고, 큐에 push한다.
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] != '.')continue;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny < 0 || ny >= R || nx < 0 || nx >= C)continue;
				if (map[ny][nx] == 'X' && melt_day[ny][nx] == 0) {
					melt_day[ny][nx] = 1;	//1일차에 녹는 좌표 표시
					q[idx].push(make_pair(ny, nx));	//큐에 넣기
				}
			}
		}
	}

	int t = 1;	//시간
	//현재 큐 안에 있는 좌표는 방금 녹은 얼음의 좌표
	while (!q[idx].empty()) {
		t++;	//시간 증가

		int size = q[idx].size();
		while (size--) {
			int y = q[idx].front().first;
			int x = q[idx].front().second;
			q[idx].pop();

			//방금 녹은 얼음 주변의 얼음 좌표에 대해
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= R || nx < 0 || nx >= C)continue;
				//아직 안 녹은 얼음일 경우
				if (map[ny][nx] == 'X' && melt_day[ny][nx] == 0) {
					//t번째 날에 녹았다고 표시하고, 다른 큐에 push한다.
					melt_day[ny][nx] = t;
					q[!idx].push(make_pair(ny, nx));
				}
			}
		}

		idx = !idx;
	}

	//출력
	cout << bsearch(0, t) << endl;

	return 0;
}