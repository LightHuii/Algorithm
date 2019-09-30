#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory.h>
#include <tuple>
using namespace std;

/*
������ ��
1. �˼������� �ݵ�� ���� �� �ִ� �Է��� �־�����.
2. �� �˼��� Ż�� ��Ʈ ���� ������ �����Ѵ�.

map�� �� ĭ�� Ȯ���Ͽ� (0,0), �˼�1, �˼�2 �� �������� BFS�� �����Ѵ�.
�� BFS����� ��� ���� ��(�� ��ǥ�� ��� -2�Ѵ�. -> 3�� ������ ������)
�ּ� ���� ���̴�.
�� ������ �� �˼��� ������ �ּ� ��� + ������ ����� �ּ� ����� ��� �����ؾ� �ϱ� �����̴�.
��, 3���� BFS�� ���� ������ ������ �� �ּҺ�� ��ǥ��.
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
	//������ ��(cost)�� -1�� �ʱ�ȭ
	for (int i = 0; i < h + 2; i++)
		for (int j = 0; j < w + 2; j++)
			cost[n][i][j] = -1;

	queue<tuple<int, int, int>>q;
	q.push(make_tuple(y, x, 0));	//��ǥ, ���� �� Ƚ��
	cost[n][y][x] = 0;				//�������� 0���� �����Ѵ�.

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
				//�׳� ������ �� �ִ� ���� ��
				if (map[ny][nx] == '.' || map[ny][nx] == '$') {
					//ó�� ���� ���̰ų� �� ���� ������� �� �� �ִ� ���� ���
					if (cost[n][ny][nx] == -1 || cost[n][ny][nx] > cnt) {
						cost[n][ny][nx] = cnt;
						q.push(make_tuple(ny, nx, cnt));
					}
				}
				//���� ��
				else if (map[ny][nx] == '#') {
					//ó�� ���� ���̰ų� �� ���� ������� �� �� �ִ� ���� ���
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
		//�ʱ�ȭ
		person.clear();
		memset(cost, 0, sizeof(cost));

		cin >> h >> w;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i + 1][j + 1];

				//�˼��� ��ǥ ����
				if (map[i + 1][j + 1] == '$')
					person.push_back(make_pair(i + 1, j + 1));
			}
		}
		//��ǥ�� Ȯ���ϱ� ������ �� �������� ä���ش�
		for (int i = 0; i < h + 2; i++) map[i][0] = '.';
		for (int i = 0; i < h + 2; i++) map[i][w + 1] = '.';
		for (int j = 0; j < w + 2; j++) map[0][j] = '.';
		for (int j = 0; j < w + 2; j++) map[h + 1][j] = '.';

		//���� BFS
		bfs(0, 0, 0);
		bfs(person[0].first, person[0].second, 1);
		bfs(person[1].first, person[1].second, 2);

		//��� ��ǥ�� ���� cost�� �����ش�
		int result = 10000;
		for (int i = 0; i < h + 2; i++) {
			for (int j = 0; j < w + 2; j++) {
				//���� ��� �� ���� ����� �ϱ� ������ 2�� ���ش�
				if (map[i][j] == '#')
					rst[i][j] = cost[0][i][j] + cost[1][i][j] + cost[2][i][j] - 2;
				else
					rst[i][j] = cost[0][i][j] + cost[1][i][j] + cost[2][i][j];
				//������ �濡 ���� �ּ� ��
				if (rst[i][j] >= 0)
					result = min(result, rst[i][j]);
			}
		}
		
		cout << result << endl;
	}

	return 0;
}