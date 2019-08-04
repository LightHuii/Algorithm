#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef struct a {
	int y, x, dir, cnt;		//��ǥ, ����, ���ݱ��� �ſ� �� 
}info;
#define MAX 50
int N;
char map[MAX][MAX];
vector<pair<int, int>>door;
int dy[] = { -1,0,1,0 };		//�ϵ�����
int dx[] = { 0,1,0,-1 };
//�鷶�� �ſ�'��' üũ�Ѵ�. ��α��� üũ�ϸ� �ٸ� ��ο� ���� �ּ� ����� ������ ���� ���� �ִ�.
//����, visited�� ���� ���� ���� ��ο��� ���� �ſ��� ����, �� ���� �ſ��� ����ϴ� ��δ� ������ �� �ֵ��� �ߴ�.
int visited[MAX][MAX] = { 0, };

//ó�� ���ۿ������� !�� ��� �ſ��� ���� �̵��غ��鼭, �ּ� �ſ� ���� ����
int bfs() {
	queue<info>q;
	for (int i = 0; i < 4; i++) {
		info tmp = { door[0].first, door[0].second, i, 0 };		//�ʱ� ��
		q.push(tmp);
	}

	int rst = INT32_MAX;		//�ּ� �ſ� ��
	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x;
		int dir = q.front().dir;
		int cnt = q.front().cnt;
		q.pop();

		if (y < 0 || y >= N || x < 0 || x >= N)continue;	//������ ����� ���� ����

		//�����Ѵٸ�
		if (y == door[1].first && x == door[1].second) {
			rst = min(rst, cnt);
			continue;		//�� �ʰ� �� ���� �ſ��� ����ϴ� ��찡 �����Ƿ� �������� �ʴ´�.
		}

		//���� ��ǥ�� ��쿡 ���� ���� ��ǥ ����
		int ny, nx, nd, nc;
		//���簡 �� ĭ�̰ų� �������� ���
		if (map[y][x] == '.' || map[y][x] == '#') {
			//������ �״�� ����
			ny = y + dy[dir];
			nx = x + dx[dir];
			nd = dir;
			nc = cnt;
			if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;
			//���� ���� Ȯ��
			//���� ���� ���� !�̰ų�, �� ���� �ſ�� �� �� �ִ� ����� ��
			if (map[ny][nx] != '*' && (visited[ny][nx] == 0 || visited[ny][nx] > cnt + 1)) {
				if(map[ny][nx] == '!')		//������ !�� ��츸 üũ���ش�.
					visited[ny][nx] = cnt + 1;
				info tmp = { ny, nx, nd, nc };
				q.push(tmp);
			}
		}
		//���� !���
		else if (map[y][x] == '!') {
			//ó���� ������ #�̹Ƿ� visit�� ǥ�� �� ���൵ �ȴ�.
			//����, ���� ���ʿ��� �ִ� ���� �ƴ϶�
			//���� ���ʸ� �̸� Ȯ���Ͽ� ť�� ���� �ʵ��� �Ͽ� �޸� �ʰ��� ���� �� �ִ�.

			//�ſ��� �����ϰ� �����ϰų�, �� ������ ���� ��θ� ����Ѵ�.
			for (int i = 0; i < 4; i++) {
				if (i == 2)continue;
				nd = (dir + i) % 4;
				ny = y + dy[nd];
				nx = x + dx[nd];
				if (i != 0)
					nc = cnt + 1;	//�ſ��� ����� ��� ī��Ʈ
				else
					nc = cnt;	//������ ��� ī��Ʈ���� �ʴ´�.
				if (ny < 0 || ny >= N || nx < 0 || nx >= N)continue;

				//����������, �� ���� �ſ��� ����� �� �ִ� ����� ��� üũ�Ͽ� ������ �� �ֵ��� �Ѵ�.
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
				door.push_back(make_pair(i, j));	//�� ��ǥ ����
		}
	}

	int rst = 0;
	rst = bfs();
	cout << rst << endl;
}