#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct _node {
	int y, x, d;
}snake;

#define MAX 101
int N, K, L;
int map[MAX][MAX] = { 0, };
pair<bool, int>visited[MAX][MAX] = { make_pair(false, -1), };
queue<pair<int, char>>q;
int dy[] = { 0,1,0,-1 };
int dx[] = { 1,0,-1,0 };	//�� �� �� ��
snake head, tail;

int direction(int d, char c) {
	//����
	if (d == 0 || d == 1) {
		if (c == 'D')
			return (d + 1) % 4;
		else
			return (d + 3) % 4;
	}
	else {
		if (c == 'D')
			return (d + 1) % 4;
		else
			return (d + 3) % 4;
	}
	return 0;
}

int main() {
	int t = 0;
	head.y = 1, head.x = 1, head.d = 0;
	tail.y = 1, tail.x = 1, tail.d = 0;

	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int y, x;
		cin >> y >> x;
		map[y][x] = 1;	//���
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int tmp;
		char c;
		cin >> tmp >> c;
		q.push(make_pair(tmp, c));
	}

	int y = 1, x = 1, dir = 0;
	int ny = y, nx = x, ndir = 0;

	//���� ������
	while (y > 0 && y <= N && x > 0 && x <= N) {
		if (!q.empty()) {
			if (t == q.front().first) {
				ndir = direction(dir, q.front().second);
				q.pop();
			}
		}
		ny = y + dy[ndir];
		nx = x + dx[ndir];

		//���� ��ǥ ������ ����
		visited[y][x].first = true;
		visited[y][x].second = ndir;	//���� ������ ����

										//����
		if (ny <= 0 || ny > N || nx <= 0 || nx > N || visited[ny][nx].first) {
			t++;
			break;
		}

		//����: ����� ������
		if (map[ny][nx] == 1) {
			head.y = ny;
			head.x = nx;
			head.d = ndir;	//����
			map[ny][nx] = 0;
		}
		//����� ������
		else {
			head.y = ny;
			head.x = nx;
			head.d = ndir;	//����
			visited[tail.y][tail.x].first = false;		//�ʱ�ȭ
			tail.d = visited[tail.y][tail.x].second;	//tail�� ���� ����
			visited[tail.y][tail.x].second = -1;		//�ʱ�ȭ
			tail.y += dy[tail.d];
			tail.x += dx[tail.d];	//���� tail�� ��ǥ
		}

		y = ny;
		x = nx;
		dir = ndir;
		t++;	//�ð� ����
	}


	cout << t << endl;
	return 0;
}
