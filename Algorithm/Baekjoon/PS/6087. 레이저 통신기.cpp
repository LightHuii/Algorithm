#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

typedef struct a {
	int y, x, dir, cnt;
}Raser;

#define MAX 100
char map[MAX][MAX];
int H, W;
vector<pair<int, int>>v;	//������, ������
int visited[MAX][MAX] = { 0, };		//������� ����� �ſ��� ������ ǥ��
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };	//�ϵ�����

int bfs() {
	queue<Raser>q;
	for (int i = 0; i < 4; i++) {
		Raser tmp = { v[0].first, v[0].second, i, 0 };	//ó���� ��� ���⿡ ����
		q.push(tmp);
	}

	int rst = INT32_MAX;	//�ּ� �ſ� ���� ����
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int dir = q.front().dir;
		int cnt = q.front().cnt;
		q.pop();

		//������ ����
		if (y == v[1].first && x == v[1].second) {
			rst = min(rst, cnt);
			continue;
		}

		//���� ��ǥ Ž��
		int ny, nx, nd;
		for (int i = 0; i < 4; i++) {
			if (i == 2)continue;	//�ݴ� ������ ����
			nd = (dir + i) % 4;
			ny = y + dy[nd];
			nx = x + dx[nd];
			if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;

			//������ ������ ��
			if (i == 0) {
				if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] > cnt)) {
					visited[ny][nx] = cnt;
					Raser tmp = { ny, nx, nd, cnt };	//ī��Ʈ���� �ʰ� ��������.
					q.push(tmp);
				}
			}
			//������ ��ȯ�ؾ� �� ��
			else {
				if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] >= cnt + 1)) {
					visited[ny][nx] = cnt + 1;
					Raser tmp = { ny, nx, nd, cnt + 1 };	//ī��Ʈ�ϰ� ��������.
					q.push(tmp);
				}
			}
		}

	}

	return rst;
}

int main()
{
	cin >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'C')
				v.push_back(make_pair(i, j));
		}
	}

	cout << bfs() << endl;
}