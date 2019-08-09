#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 50
int m, n;
int map[MAX][MAX];
int visited[MAX][MAX];		//각 좌표에 대해 방 번호를 저장
int dy[] = { 0,-1,0,1 };
int dx[] = { -1,0,1,0 };	//서북동남
int first = 0, second = 0, third = 0;	//결과 값
bool room_adj[MAX * MAX][MAX * MAX];	//방과 방 사이가 인접해 있는지 확인
bool visited2[MAX][MAX];				//두 번째 bfs시 사용
int room_big[MAX * MAX] = { 0, };		//각 방의 크기 저장

//한 방의 크기를 리턴
int roomArea(int y, int x) {
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	int cnt = 0;
	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		visited[y][x] = first;
		cnt++;

		for (int i = 0; i < 4; i++) {
			int mul = 1 << i;
			if (map[y][x] & mul)continue;	//0이 나와야 열린 길
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= m || nx < 0 || nx >= n)continue;

			if (visited[ny][nx] == -1) {
				visited[ny][nx] = first;
				q.push(make_pair(ny, nx));
			}
		}
	}
	return cnt;
}

//각 방을 방문하며 방과 방 사이가 인접해 있는지 체크하는 함수
void bfs(int num, int y, int x) {		//방 번호
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));

	while (!q.empty()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		visited2[y][x] = true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= m || nx < 0 || nx >= n)continue;
			if (visited[ny][nx] != num) {
				room_adj[num][visited[ny][nx]] = true;
				room_adj[visited[ny][nx]][num] = true;
			}
			else if (!visited2[ny][nx]) {
				visited2[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			visited[i][j] = -1;
		}
	}

	//방의 개수, 가장 큰 방의 크기, 모든 좌표에 대해 방 번호 지정
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == -1) {
				int tmp = roomArea(i, j);
				second = max(second, tmp);
				room_big[first] = tmp;	//방의 크기 저장
				first++;
			}
		}
	}

	//각 방의 관계 체크
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (!visited2[i][j]) {
				bfs(visited[i][j], i, j);	//방 번호
			}
		}
	}

	//인접한 방의 크기의 합이 가장 큰 것을 찾음
	for (int i = 0; i < first - 1; i++) {
		for (int j = i + 1; j < first; j++) {
			if (room_adj[i][j])
				third = max(third, room_big[i] + room_big[j]);
		}
	}

	cout << first << endl << second << endl << third << endl;

	return 0;
}