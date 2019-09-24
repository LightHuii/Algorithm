#include <iostream>
#include <algorithm>
#include <memory.h>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;
/*
	1. map을 전체 dfs 돌려 섬의 개수와 각 섬의 좌표 정보를 저장

	2. 섬 별로 섬의 모든 좌표에 대해 다리를 만들어 사용 가능한 다리 정보 저장
	-> 대강 섬의 모든 좌표개수가 100개라고 치면, 100*10*4 = 4000밖에 안 됨
	-> 사용 가능한 다리는 섬(A<->B)의 배열에 다리의 길이의 최소값으로 저장

	3. 현재 가지고 있는 다리의 정보를 기반으로 섬끼리 연결
	-> 섬끼리는 하나의 다리로만 연결되어야 하며, 모든 섬이 연결되어야 한다.
	-> 조합으로 다리를 선택하고, 모든 섬이 연결되어 있는지는 새로운 BFS로 확인
*/

#define MAX 10
int map[MAX][MAX];		//섬의 내용을 번호로 바꾸기
bool visited[MAX][MAX];
int N, M;
int island_cnt = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
vector<vector<pair<int, int>>>island;	//각 섬의 좌표 정보
int bridge[7][7];	//다리 정보1
tuple<int, int, int>bridgeInfo[100];	//다리 정보2
int bridge_cnt = 0;			//모든 다리의 개수
bool bridge_connect[7][7];	//다리 연결 표시
int rst = INT32_MAX;		//결과 값

//섬 좌표 정보 만들기
void make_IslandInfo(int y, int x) {
	visited[y][x] = true;
	map[y][x] = island_cnt;
	island[island_cnt].push_back(make_pair(y, x));

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= N || nx < 0 || nx >= M)continue;
		if (!visited[ny][nx] && map[ny][nx]) {
			make_IslandInfo(ny, nx);
		}
	}
}

//섬이 서로 모두 연결됐는지 확인
bool bfs() {
	bool visit[7];
	memset(visit, false, sizeof(visit));
	queue<int>q;
	q.push(1);

	int cnt = 0;
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		visit[curr] = true;
		cnt++;

		for (int next = 1; next <= island_cnt; next++) {
			//자기자신이거나 연결이 안되어 있다면
			if (curr == next || !bridge_connect[curr][next])continue;
			if (!visit[next]) {
				visit[next] = true;
				q.push(next);
			}
		}
	}

	//방문 수가 전체 섬의 개수와 같다면
	if (cnt == island_cnt)
		return true;
	else
		return false;
}

//다리 선택
void dfs(int idx, int cnt, int sum) {
	if (cnt > 0) {
		//연결됐는지 매번 확인
		if (bfs()) {
			rst = min(rst, sum);
		}
	}
	if (idx >= bridge_cnt)return;	//종료

	//다리 연결
	bridge_connect[get<0>(bridgeInfo[idx])][get<1>(bridgeInfo[idx])] = true;
	bridge_connect[get<1>(bridgeInfo[idx])][get<0>(bridgeInfo[idx])] = true;
	dfs(idx + 1, cnt + 1, sum + get<2>(bridgeInfo[idx]));

	//다리 해제
	bridge_connect[get<0>(bridgeInfo[idx])][get<1>(bridgeInfo[idx])] = false;
	bridge_connect[get<1>(bridgeInfo[idx])][get<0>(bridgeInfo[idx])] = false;
	dfs(idx + 1, cnt, sum);
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	island.resize(7);	//1 ~ 6까지 사용
	//다리 길이 초기화
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 6; j++)
			bridge[i][j] = INT32_MAX;

	//섬 정보 저장 및 map 갱신
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j] && map[i][j]) {
				island_cnt++;
				make_IslandInfo(i, j);
			}
		}
	}
	memset(visited, false, sizeof(visited));

	//다리 정보 구하기
	for (int i = 1; i <= island_cnt; i++) {
		for (int j = 0; j < (int)island[i].size(); j++) {
			//네 방향으로 이동하며 연결할 수 있는지 확인
			for (int d = 0; d < 4; d++) {
				int y = island[i][j].first;
				int x = island[i][j].second;
				int ny = y, nx = x;
				int len = 0;	//다리 길이
				bool flag = true;	//연결하지 못 할 경우
				int other = -1;		//다른 섬의 번호

				while (1) {
					ny += dy[d];
					nx += dx[d];
					//연결되지 못 한다면
					if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
						flag = false;
						break;
					}
					//다른 섬을 만났을 때
					else if (map[ny][nx] != 0) {
						//길이가 1이거나 자기 자신이라면
						if (len == 1 || map[ny][nx] == i)
							flag = false;
						other = map[ny][nx];
						break;
					}
					len++;
				}

				//연결할 수 있을 경우
				if (flag) {
					bridge[i][other] = min(len, bridge[i][other]);
					bridge[other][i] = min(len, bridge[other][i]);
				}
			}
		}
	}

	//다리 정보 정리
	for (int i = 1; i < island_cnt; i++) {
		for (int j = i + 1; j <= island_cnt; j++) {
			if (bridge[i][j] < INT32_MAX) {
				bridgeInfo[bridge_cnt++] = make_tuple(i, j, bridge[i][j]);
			}
		}
	}

	//조합 및 연결하여 전부연결될 때의 최소 value 구하기
	dfs(0, 0, 0);
	if (rst < INT32_MAX)
		cout << rst << endl;
	else
		cout << -1 << endl;
	return 0;
}