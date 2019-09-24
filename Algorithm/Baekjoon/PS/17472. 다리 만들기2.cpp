#include <iostream>
#include <algorithm>
#include <memory.h>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;
/*
	1. map�� ��ü dfs ���� ���� ������ �� ���� ��ǥ ������ ����

	2. �� ���� ���� ��� ��ǥ�� ���� �ٸ��� ����� ��� ������ �ٸ� ���� ����
	-> �밭 ���� ��� ��ǥ������ 100����� ġ��, 100*10*4 = 4000�ۿ� �� ��
	-> ��� ������ �ٸ��� ��(A<->B)�� �迭�� �ٸ��� ������ �ּҰ����� ����

	3. ���� ������ �ִ� �ٸ��� ������ ������� ������ ����
	-> �������� �ϳ��� �ٸ��θ� ����Ǿ�� �ϸ�, ��� ���� ����Ǿ�� �Ѵ�.
	-> �������� �ٸ��� �����ϰ�, ��� ���� ����Ǿ� �ִ����� ���ο� BFS�� Ȯ��
*/

#define MAX 10
int map[MAX][MAX];		//���� ������ ��ȣ�� �ٲٱ�
bool visited[MAX][MAX];
int N, M;
int island_cnt = 0;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
vector<vector<pair<int, int>>>island;	//�� ���� ��ǥ ����
int bridge[7][7];	//�ٸ� ����1
tuple<int, int, int>bridgeInfo[100];	//�ٸ� ����2
int bridge_cnt = 0;			//��� �ٸ��� ����
bool bridge_connect[7][7];	//�ٸ� ���� ǥ��
int rst = INT32_MAX;		//��� ��

//�� ��ǥ ���� �����
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

//���� ���� ��� ����ƴ��� Ȯ��
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
			//�ڱ��ڽ��̰ų� ������ �ȵǾ� �ִٸ�
			if (curr == next || !bridge_connect[curr][next])continue;
			if (!visit[next]) {
				visit[next] = true;
				q.push(next);
			}
		}
	}

	//�湮 ���� ��ü ���� ������ ���ٸ�
	if (cnt == island_cnt)
		return true;
	else
		return false;
}

//�ٸ� ����
void dfs(int idx, int cnt, int sum) {
	if (cnt > 0) {
		//����ƴ��� �Ź� Ȯ��
		if (bfs()) {
			rst = min(rst, sum);
		}
	}
	if (idx >= bridge_cnt)return;	//����

	//�ٸ� ����
	bridge_connect[get<0>(bridgeInfo[idx])][get<1>(bridgeInfo[idx])] = true;
	bridge_connect[get<1>(bridgeInfo[idx])][get<0>(bridgeInfo[idx])] = true;
	dfs(idx + 1, cnt + 1, sum + get<2>(bridgeInfo[idx]));

	//�ٸ� ����
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

	island.resize(7);	//1 ~ 6���� ���
	//�ٸ� ���� �ʱ�ȭ
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 6; j++)
			bridge[i][j] = INT32_MAX;

	//�� ���� ���� �� map ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j] && map[i][j]) {
				island_cnt++;
				make_IslandInfo(i, j);
			}
		}
	}
	memset(visited, false, sizeof(visited));

	//�ٸ� ���� ���ϱ�
	for (int i = 1; i <= island_cnt; i++) {
		for (int j = 0; j < (int)island[i].size(); j++) {
			//�� �������� �̵��ϸ� ������ �� �ִ��� Ȯ��
			for (int d = 0; d < 4; d++) {
				int y = island[i][j].first;
				int x = island[i][j].second;
				int ny = y, nx = x;
				int len = 0;	//�ٸ� ����
				bool flag = true;	//�������� �� �� ���
				int other = -1;		//�ٸ� ���� ��ȣ

				while (1) {
					ny += dy[d];
					nx += dx[d];
					//������� �� �Ѵٸ�
					if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
						flag = false;
						break;
					}
					//�ٸ� ���� ������ ��
					else if (map[ny][nx] != 0) {
						//���̰� 1�̰ų� �ڱ� �ڽ��̶��
						if (len == 1 || map[ny][nx] == i)
							flag = false;
						other = map[ny][nx];
						break;
					}
					len++;
				}

				//������ �� ���� ���
				if (flag) {
					bridge[i][other] = min(len, bridge[i][other]);
					bridge[other][i] = min(len, bridge[other][i]);
				}
			}
		}
	}

	//�ٸ� ���� ����
	for (int i = 1; i < island_cnt; i++) {
		for (int j = i + 1; j <= island_cnt; j++) {
			if (bridge[i][j] < INT32_MAX) {
				bridgeInfo[bridge_cnt++] = make_tuple(i, j, bridge[i][j]);
			}
		}
	}

	//���� �� �����Ͽ� ���ο���� ���� �ּ� value ���ϱ�
	dfs(0, 0, 0);
	if (rst < INT32_MAX)
		cout << rst << endl;
	else
		cout << -1 << endl;
	return 0;
}