#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<memory.h>
using namespace std;

#define MAX 20
int w, h;
char map[MAX][MAX];
bool visited[MAX][MAX];
pair<int, int>robot;
vector<pair<int, int>>dirt_poten;
int dirt_cnt = 0;
int dist[10][10] = { 0, };	//��ȣ 0~9�� ��ȣ �Ÿ� ����
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int dirt[10];
bool dirt_selected[10];
int rst = INT32_MAX;


//a����, b��ǥ�� �Ÿ� ���� -> dist[a][b]�� ����
void bfs(int a, int b) {
	queue<pair<int, int>>q;
	q.push(make_pair(dirt_poten[a].first, dirt_poten[a].second));

	memset(visited, false, sizeof(visited));

	int t = 0;	//�Ÿ�, �ð�
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			visited[y][x] = true;
			
			if (y == dirt_poten[b].first && x == dirt_poten[b].second) {
				dist[a][b] = t;
				return;
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny < 0 || ny >= h || nx < 0 || nx >= w)continue;
				if (!visited[ny][nx] && map[ny][nx]!='x') {
					visited[ny][nx] = true;
					q.push(make_pair(ny, nx));
				}
			}
		}
		t++;
	}

	dist[a][b] = -1;
	return;
}

//������ ���� ��ǥ�� ����
void dfs(int cnt) {
	if (cnt >= dirt_cnt) {
		int distance = dist[dirt_cnt][dirt[0]];	//�κ��� ó�� ������ �Ÿ� �켱
		if (distance > -1) {
			for (int i = 1; i < dirt_cnt; i++) {
				int tmp = dist[dirt[i]][dirt[i - 1]];
				distance += tmp;
				
				if (tmp == -1)return;
			}
			rst = min(distance, rst);
		}

		return;
	}

	for (int i = 0; i < dirt_cnt; i++) {
		if (!dirt_selected[i]) {
			dirt_selected[i] = true;
			
			dirt[cnt] = i;
			dfs(cnt + 1);

			dirt_selected[i] = false;
		}
	}
}

int main() {
	while (1) {
		cin >> w >> h;
		if (w == 0 && h == 0)break;

		//�ʱ�ȭ
		rst = INT32_MAX;
		dirt_cnt = 0;
		memset(dirt_selected, false, sizeof(dirt_selected));
		dirt_poten.clear();

		//�Է� �� ��ǥ, ���� ����
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
				if (map[i][j] == 'o') {
					robot.first = i;
					robot.second = j;
				}
				else if (map[i][j] == '*') {
					dirt_poten.push_back(make_pair(i, j));
					dirt_cnt++;
				}
			}
		}

		//�κ� ��ġ�� �������� �߰�
		dirt_poten.push_back(make_pair(robot.first, robot.second));

		//�κ� ���� ������ �Ÿ� ����
		for (int i = 0; i < (int)dirt_poten.size(); i++)
			for (int j = 0; j < (int)dirt_poten.size(); j++)
				if (i != j)
					bfs(i, j);

		dfs(0);
		if (rst == INT32_MAX)
			cout << -1 << endl;
		else
			cout << rst << endl;
	}

	return 0;
}