#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define MAX 101
int T, N;
int map[MAX][MAX];
int rst;
int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };	//��0, ��1, ��2, ��3
pair<int, int>worm1[11];
pair<int, int>worm2[11];
int sy, sx;	//���� ��ǥ

void init() {
	rst = 0;
	for (int i = 0; i <= 10; i++) {
		worm1[i].first = -1;
		worm1[i].second = -1;
		worm2[i].first = -1;
		worm2[i].second = -1;
	}
}

//���, ���� ����� �� ���� ����
//��� ��ǥ��, ��� �������� �Դ���, � �������
int set_dir(int y, int x, int dir, int block) {
	//���� ���
	if (block == 0) {
		if (y < 0)
			return 2;	//��->��
		else if (y >= N)
			return 3;	//��->��
		else if (x < 0)
			return 0;	//��->��
		else if (x >= N)
			return 1;	//��->��
	}
	//����� ���
	else {
		if (block == 1) {
			if (dir == 3)
				return 2;	//�� -> ��
			else if (dir == 0)
				return 1;	//�� -> ��
			else if (dir == 2)
				return 0;	//�� -> ��
			else if (dir == 1)
				return 3;	//�� -> ��
		}
		else if (block == 2) {
			if (dir == 3)
				return 0;	//�� -> ��
			else if (dir == 0)
				return 1;	//�� -> ��
			else if (dir == 2)
				return 3;	//�� -> ��
			else if (dir == 1)
				return 2;	//�� -> ��
		}
		else if (block == 3) {
			if (dir == 3)
				return 1;	//�� -> ��
			else if (dir == 0)
				return 2;	//�� -> ��
			else if (dir == 2)
				return 3;	//�� -> ��
			else if (dir == 1)
				return 0;	//�� -> ��
		}
		else if (block == 4) {
			if (dir == 3)
				return 2;	//�� -> ��
			else if (dir == 0)
				return 3;	//�� -> ��
			else if (dir == 2)
				return 1;	//�� -> ��
			else if (dir == 1)
				return 0;	//�� -> ��
		}
		else if (block == 5) {
			if (dir == 3)
				return 2;	//�� -> ��
			else if (dir == 0)
				return 1;	//�� -> ��
			else if (dir == 2)
				return 3;	//�� -> ��
			else if (dir == 1)
				return 0;	//�� -> ��
		}
	}
	return 0;
}

void run(int y, int x, int dir) {
	//�ϴ� �� ĭ �̵�
	int cy = y;
	int cx = x;
	int score = 0;

	//�ϴ� �����ϰ�, ���� ��ǥ�� ���� �Ǵ��ϱ�

	while (1) {
		//����
		cy += dy[dir];
		cx += dx[dir];

		//cout << "y, x: " << cy << ", " << cx << endl;
		//cout << "score: " << score << endl;
		//cout << "sy, sx: " << sy << ", " << sx << endl << endl;;

		//���� ������ ��
		if ((cy == sy && cx == sx) || map[cy][cx] == -1) {
			rst = max(rst, score);
			break;
		}

		//���� ��
		if (cy < 0 || cx < 0 || cy >= N || cx >= N) {
			dir = set_dir(cy, cx, dir, 0);
			score++;
		}
		//����� ��
		else if (map[cy][cx] >= 1 && map[cy][cx] <= 5) {
			dir = set_dir(cy, cx, dir, map[cy][cx]);
			score++;
		}
		//��Ȧ�� ���
		else if (map[cy][cx] >= 6 && map[cy][cx] <= 10) {
			int ty, tx;
			if (worm1[map[cy][cx]].first == cy && worm1[map[cy][cx]].second == cx) {
				ty = worm2[map[cy][cx]].first;
				tx = worm2[map[cy][cx]].second;
				cy = ty;
				cx = tx;
			}
			else if (worm2[map[cy][cx]].first == cy && worm2[map[cy][cx]].second == cx) {
				ty = worm1[map[cy][cx]].first;
				tx = worm1[map[cy][cx]].second;
				cy = ty;
				cx = tx;
			}
		}
	}
}

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	init();

	while (Ttmp--) {
		cin >> N;

		//�Է�
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];

				//��Ȧ �̶��
				if (map[i][j] >= 6 && map[i][j] <= 10) {
					if (worm1[map[i][j]].first == -1) {
						worm1[map[i][j]].first = i;
						worm1[map[i][j]].second = j;
					}
					else {
						worm2[map[i][j]].first = i;
						worm2[map[i][j]].second = j;
					}
				}
			}
		}


		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int d = 0; d < 4; d++) {
					sy = i;
					sx = j;	//������ ����
							//���, ��Ȧ, ��Ȧ�� ��� ����
					if (map[i][j] == -1 || (map[i][j] >= 1 && map[i][j] <= 10))continue;
					run(i, j, d);
				}
			}
		}
		cout << '#' << T - Ttmp << ' ' << rst << endl;
		init();
	}
}