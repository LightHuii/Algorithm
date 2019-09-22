#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 1500
int R, C;
char map[MAX][MAX];
int melt_day[MAX][MAX] = { 0, };	//������ ��� ��¥�� ���
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
pair<int, int> swan[2];	//���� ��ǥ
int visited[MAX][MAX];

//t���� ������ �̵��� �� �ִ�. 
bool bfs(int t) {
	queue<pair<int, int>>q;
	q.push(swan[0]);	//�������� ����

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		visited[y][x] = t;		//visited�� �ʱ�ȭ���� �ʰ� ���
		q.pop();

		//�ٸ� ���� ã���� true
		if (y == swan[1].first && x == swan[1].second)
			return true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= R || nx < 0 || nx >= C)continue;

			//���̰ų�, t��°�� �̵��� �� �ִ� ������ ���
			if (map[ny][nx] == '.' || (map[ny][nx] == 'X' && melt_day[ny][nx] <= t)) {
				if (visited[ny][nx] != t) {
					visited[ny][nx] = t;		//�湮 ǥ��
					q.push(make_pair(ny, nx));
				}
			}
		}
	}

	return false;
}

//0 ~ t��° �� �� �ּҷ� �� �� �ִ� ���� ã�� �̺�Ž��
int bsearch(int s, int e) {
	int start = s, end = e;
	int mid = (start + end) / 2;
		
	while (start <= end) {
		mid = (start + end) / 2;
		if (start == end)break;		//start == end == mid�� �� Ž�� �Ϸ�

		//������ ���� ���� �� ���� ��
		if (bfs(mid))
			end = mid;	//mid�� ���� �� �� �����Ƿ�
		//���� �� ���� ��
		else
			start = mid + 1;	//mid�� ���� �� �� �����Ƿ�
	}

	return mid;
}

int main()
{
	cin >> R >> C;

	//�Է�
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

	//��ó��
	queue<pair<int, int>>q[2];	//ť �� ���� ������ ���� ���
	bool idx = 0;

	//1������ ��� ������ ��ǥ�� ǥ���ϰ�, ť�� push�Ѵ�.
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] != '.')continue;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny < 0 || ny >= R || nx < 0 || nx >= C)continue;
				if (map[ny][nx] == 'X' && melt_day[ny][nx] == 0) {
					melt_day[ny][nx] = 1;	//1������ ��� ��ǥ ǥ��
					q[idx].push(make_pair(ny, nx));	//ť�� �ֱ�
				}
			}
		}
	}

	int t = 1;	//�ð�
	//���� ť �ȿ� �ִ� ��ǥ�� ��� ���� ������ ��ǥ
	while (!q[idx].empty()) {
		t++;	//�ð� ����

		int size = q[idx].size();
		while (size--) {
			int y = q[idx].front().first;
			int x = q[idx].front().second;
			q[idx].pop();

			//��� ���� ���� �ֺ��� ���� ��ǥ�� ����
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (ny < 0 || ny >= R || nx < 0 || nx >= C)continue;
				//���� �� ���� ������ ���
				if (map[ny][nx] == 'X' && melt_day[ny][nx] == 0) {
					//t��° ���� ��Ҵٰ� ǥ���ϰ�, �ٸ� ť�� push�Ѵ�.
					melt_day[ny][nx] = t;
					q[!idx].push(make_pair(ny, nx));
				}
			}
		}

		idx = !idx;
	}

	//���
	cout << bsearch(0, t) << endl;

	return 0;
}