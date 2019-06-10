#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 50
int map[MAX][MAX];
int visited[MAX][MAX] = { 0, };
int y, x, d;	//���� ��ǥ, ����
int N, M;
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

int main() {
	cin >> N >> M;
	cin >> y >> x >> d;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	int cnt = 0;	//û���� ĭ�� ����
	int ny = y, nx = x, nd = d;	//���� ��ǥ�� ����

	while (1) {
		//û���Ѵ�.
		if (map[y][x] == 0 && visited[y][x] == 0) {
			cnt++;
			visited[y][x] = cnt;
		}


		//�� �� Ž��
		nd = d - 1;
		if (nd < 0)nd = 3;

		ny = y + dy[nd];
		nx = x + dx[nd];	//���� ��ǥ

							//û���� �� �ִٸ� ����
		if (map[ny][nx] == 0 && visited[ny][nx] == 0) {
			d = nd;	//ȸ��
			y = ny;
			x = nx;
			continue;
		}
		//û���� �� ���ٸ�
		else {
			int tmp_cnt = 0;
			while (map[ny][nx] != 0 || visited[ny][nx] != 0) {		//�� ���� û���� �� ���� ����
																	//�� �� Ž��
				nd = nd - 1;
				if (nd < 0)nd = 3;

				ny = y + dy[nd];
				nx = x + dx[nd];	//���� ��ǥ
				tmp_cnt++;	//�� Ƚ��
				if (tmp_cnt == 4)break;
			}
			if (tmp_cnt == 4) {
				//����
				nd = (d + 2) % 4;
				if (map[y + dy[nd]][x + dx[nd]] == 1)
					break;
				y = y + dy[nd];
				x = x + dx[nd];
				nd = d;
				continue;
			}
			d = (nd + 1) % 4;
		}
	}

	cout << cnt << endl;

	return 0;
}