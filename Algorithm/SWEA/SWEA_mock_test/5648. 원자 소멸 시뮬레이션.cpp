#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
using namespace std;

typedef struct _node {
	int y, x;
	int e, d;
	bool live;
}atom;

#define MAX 2001
int T;
int map[MAX][MAX] = { 0, };
vector<atom> v;
int dy[] = { 1, -1, 0, 0 };	//��: y����, ��: y����, ��, ��
int dx[] = { 0, 0, -1, 1 };	//�� �� ��:x����, ��: x����

int ddy[] = { 1, -1, 0, 0, 1, -1, 1, -1, 0, 2, 0, -2 };
int ddx[] = { 0, 0, -1, 1, 1, -1, -1, 1, 2, 0, -2, 0 };

bool check(int y, int x, int dir, int ny, int nx, int ndir) {
	//��
	if (dir == 0) {
		if (ny == y + 1 && nx == x - 1 && ndir == 3)
			return true;
		else if (ny == y + 2 && nx == x && ndir == 1)
			return true;
		else if (ny == y + 1 && nx == x + 1 && ndir == 2)
			return true;
		else return false;
	}
	//��
	else if (dir == 1) {
		if (ny == y - 1 && nx == x - 1 && ndir == 3)
			return true;
		else if (ny == y - 2 && nx == x && ndir == 0)
			return true;
		else if (ny == y - 1 && nx == x + 1 && ndir == 2)
			return true;
		else return false;
	}
	//��
	else if (dir == 2) {
		if (ny == y + 1 && nx == x - 1 && ndir == 1)
			return true;
		else if (ny == y && nx == x - 2 && ndir == 3)
			return true;
		else if (ny == y - 1 && nx == x - 1 && ndir == 0)
			return true;
		else return false;
	}
	//��
	else if (dir == 3) {
		if (ny == y + 1 && nx == x + 1 && ndir == 1)
			return true;
		else if (ny == y && nx == x + 2 && ndir == 2)
			return true;
		else if (ny == y - 1 && nx == x + 1 && ndir == 0)
			return true;
		else return false;
	}
	return false;
}

//���� �Ǵ�
bool front_atom(int d1, int d2) {
	switch (d1)
	{
	case 0:if (d2 == 1)return true;
		   else return false;
		   break;
	case 1:if (d2 == 0)return true;
		   else return false;
		   break;
	case 2:if (d2 == 3)return true;
		   else return false;
		   break;
	case 3:if (d2 == 2)return true;
		   else return false;
		   break;
	default:
		break;
	}
	return false;
}

int main() {
	int N, y, x, d, k;
	cin >> T;
	int Ttmp = T;

	while (Ttmp--) {
		int rst = 0, cnt;	//��� ��, ���� ����

		cin >> N;
		v.resize(N + 1);

		for (int i = 1; i <= N; i++) {
			cin >> x >> y >> d >> k;
			atom tmp;
			tmp.d = d;
			tmp.e = k;
			tmp.y = y + 1000;
			tmp.x = x + 1000;
			tmp.live = true;
			v[i] = tmp;
		}

		cnt = N;
		//��尡 ���� ������ ������
		while (cnt > 0) {
			//����ִ� ���ڿ� ����: �ϴ� map�� ����
			for (int i = 1; i <= N; i++) {
				if (v[i].y < 0 || v[i].y>2000 || v[i].x < 0 || v[i].x>2000 || !v[i].live)continue;
				map[v[i].y][v[i].x] = i;
			}

			//�� ���ڿ� ���� �̵� ��, üũ�ϰ� �̵�
			for (int i = 1; i <= N; i++) {
				y = v[i].y, x = v[i].x;
				//������ ���ڸ� ����
				if (!v[i].live || y < 0 || y>2000 || x < 0 || x>2000)continue;

				int dir = v[i].d;
				int ny = y + dy[v[i].d];
				int nx = x + dx[v[i].d];	//���� ��ǥ: 1�Ÿ� ����
				int other; //�ٸ� ���� ��ȣ

						   //1�Ÿ��� ���ڰ� ���� ���
				if (ny >= 0 && ny <= 2000 && nx >= 0 && nx <= 2000 && map[ny][nx] != 0) {
					other = map[ny][nx];

					//�������� �� ���
					if (front_atom(v[other].d, dir)) {


						//�� �� �״´�
						rst += (v[i].e + v[other].e);
						v[i].live = false;
						v[other].live = false;
						cnt -= 2;
						map[v[i].y][v[i].x] = 0;
						map[v[other].y][v[other].x] = 0;


						//�������ڷ� �Ѿ
						continue;
					}
					else {
						//0.5�� �� ����� ���ڸ� ó�� ���ֱ�
						int next = map[v[other].y + dy[v[other].d]][v[other].x + dx[v[other].d]];

						if (next != 0) {
							//�����̶��
							if (front_atom(v[other].d, v[next].d)) {
								rst += (v[next].e + v[other].e);
								v[next].live = false;
								v[other].live = false;
								map[v[next].y][v[next].x] = 0;
								map[v[other].y][v[other].x] = 0;
								cnt -= 2;
							}
						}
						//������ �ƴϰų�, ���ų�, �̹� ó���� �ƴٸ�, i�� �Ÿ� 2 ó���� �Ѿ��
					}
				}

				//�Ÿ� 2 ���ڵ� ó��
				bool flag = false;	//�������� Ȯ��
				for (int j = 0; j < 12; j++) {
					int nny, nnx;
					nny = y + ddy[j];
					nnx = x + ddx[j];
					if (nny < 0 || nny>2000 || nnx < 0 || nnx>2000 || map[nny][nnx] == 0)continue;
					int next = map[nny][nnx];

					if (check(y, x, dir, nny, nnx, v[next].d) && v[next].live) {
						//next ����
						rst += v[next].e;
						v[next].live = false;
						map[v[next].y][v[next].x] = 0;
						flag = true;
						cnt--;
					}
				}

				//�����ٸ� i�� ����
				if (flag) {
					rst += v[i].e;
					v[i].live = false;
					map[v[i].y][v[i].x] = 0;
					cnt--;
				}
				else {
					//�̵�
					map[v[i].y][v[i].x] = 0;
					v[i].y = ny;
					v[i].x = nx;

					//�̵� �� ������ �����ٸ� ����
					if (v[i].y < 0 || v[i].y>2000 || v[i].x < 0 || v[i].x>2000) {
						v[i].live = false;
						cnt--;
					}
				}
			}

			//�� ���ο� �ִ� ��� ���ҵ鿡 ���� �ʿ��� ����
			for (int i = 1; i <= N; i++) {
				if (!v[i].live)continue;
				if (v[i].y < 0 || v[i].y>2000 || v[i].x < 0 || v[i].x>2000)continue;
				map[v[i].y][v[i].x] = 0;
			}

			//cout << "����: " << i << endl;
			////if (rst > 0) {
			//	for (int k = 1; k <= N; k++) {
			//		cout << "i: (" << v[k].y << ", " << v[k].x << "), d: " << v[k].d << ", " << v[k].live << endl;
			//	}
			//	cout << "cnt, rst: " << cnt << ", " << rst << endl;
			//	cout << endl;
			////}

		}

		cout << '#' << T - Ttmp << ' ' << rst << endl;
		v.clear();
		memset(map, 0, sizeof(map));
	}


	return 0;
}