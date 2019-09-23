#include <iostream>
#include <algorithm>
#include <string>
#include <memory.h>
using namespace std;

#define MAX 10
#define NUM(y, x) (((y - 1) / 3) * 3 + ((x - 1) / 3) + 1)
#define CAN_SET(y, x, n) (!ver[x][n] && !hor[y][n] && !cell[NUM(y, x)][n])
int map[MAX][MAX] = { 0, };
bool ver[MAX][MAX];		//�� üũ
bool hor[MAX][MAX];		//�� üũ
bool cell[MAX][MAX];	//3*3 ���� ���� üũ
bool domino[MAX][MAX];		//���̳� ���� üũ
int dy[] = { 1, 0 };	
int dx[] = { 0, 1 };
int N;
bool flag;
int puzzle_cnt = 1;

void init() {
	memset(map, 0, sizeof(map));
	memset(ver, false, sizeof(ver));
	memset(hor, false, sizeof(hor));
	memset(cell, false, sizeof(cell));
	memset(domino, false, sizeof(domino));
	flag = false;
}

//���̳� ����
void set_domi(int y, int x, int n) {
	map[y][x] = n;
	ver[x][n] = true;
	hor[y][n] = true;
	cell[NUM(y, x)][n] = true;
}

//���̵� ����
void unset_domi(int y, int x, int n) {
	map[y][x] = 0;
	ver[x][n] = false;
	hor[y][n] = false;
	cell[NUM(y, x)][n] = false;
}

void dfs(int y, int x, int cnt) {
	//�̹� ���� ������ ��� 
	if (flag)return;

	//��ǥ�� ������ �Դٸ�
	if (y >= 10) {
		//���� �� �ִ� ���̳�� ���� ������ ��
		if (cnt == 36 - N) {
			//���
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					cout << map[i][j];
				}
				cout << endl;
			}

			flag = true;	//�̹� ������ ���Դٰ� ǥ��
			return;
		}
		return;
	}
	//���� �� �ִ� ���̳��� ������ �� ���� ���� ��� ����
	if (cnt > 36 - N)return;

	//���� ��ǥ
	int ny = y, nx = x + 1;
	if (nx >= 10) {
		nx = 1;
		ny++;
	}

	//���� �ڸ��� ����ִٸ�
	if (map[y][x] == 0) {
		for (int i = 1; i <= 9; i++) {
			//ù ��° ���� �Ǵ�
			if (!CAN_SET(y, x, i)) continue;	//���� �� ���ٸ�
			//ù ��° ����
			set_domi(y, x, i);

			for (int j = 1; j <= 9; j++) {
				if (i == j || domino[i][j] || domino[j][i])continue;
				domino[i][j] = true;
				domino[j][i] = true;

				//�� ��° ���� �Ǵ�
				for (int k = 0; k < 2; k++) {
					int sy = y + dy[k];
					int sx = x + dx[k];
					if (sy < 1 || sy > 9 || sx < 1 || sx > 9)continue;
					//���� �� ���ٸ�
					if (map[sy][sx] != 0 || !CAN_SET(sy, sx, j))continue;
					//�� ��° ����
					set_domi(sy, sx, j);

					//��������
					dfs(ny, nx, cnt + 1);

					//�� ��° ����
					unset_domi(sy, sx, j);
				}
				domino[i][j] = false;
				domino[j][i] = false;
			}

			//ù ��° ����
			unset_domi(y, x, i);
		}
	}
	//�ƴ϶�� ���� ��ǥ��
	else
		dfs(ny, nx, cnt);
}

int main()
{
	while (1) {
		cin >> N;
		if (N == 0)break;

		//�ʱ�ȭ
		init();

		//�Է� �� üũ
		for (int i = 0; i < N; i++) {
			string str;
			int n1, n2, y, x;

			cin >> n1 >> str;
			y = (int)(str[0] - 'A' + 1);
			x = (int)(str[1] - '0');
			set_domi(y, x, n1);

			cin >> n2 >> str;
			y = (int)(str[0] - 'A' + 1);
			x = (int)(str[1] - '0');
			set_domi(y, x, n2);

			domino[n1][n2] = true;
			domino[n2][n1] = true;
		}

		for (int i = 1; i <= 9; i++) {
			string str;
			int y, x;
			cin >> str;
			y = (int)(str[0] - 'A' + 1);
			x = (int)(str[1] - '0');
			set_domi(y, x, i);
		}

		cout << "Puzzle " << puzzle_cnt++ << endl;
		dfs(1, 1, 0);	//(1, 1)���� �����ϰ�, ���̳븦 �ϳ��� ���� �ʾҴٸ�
	}

	return 0;
}