#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 20
int N;
int rst = 0;
bool visited[MAX][MAX];
int map[MAX][MAX];

//���⿡ ���� ����
void arrange(int dir) {
	int idx;
	int tmp[MAX];

	if (dir == 0) {
		for (int j = 0; j < N; j++) {
			idx = 0;
			for (int i = 0; i < N; i++) {
				if (map[i][j] != 0) {
					tmp[idx++] = map[i][j];
					map[i][j] = 0;
				}
			}
			for (int i = 0; i < idx; i++)
				map[i][j] = tmp[i];
		}
	}
	else if (dir == 1) {
		for (int i = 0; i < N; i++) {
			idx = 0;
			for (int j = N - 1; j >= 0; j--) {
				if (map[i][j] != 0) {
					tmp[idx++] = map[i][j];
					map[i][j] = 0;
				}
			}
			for (int j = N - 1; j >= N - idx; j--)
				map[i][j] = tmp[(N - 1) - j];
		}
	}
	else if (dir == 2) {
		for (int j = 0; j < N; j++) {
			idx = 0;
			for (int i = N - 1; i >= 0; i--) {
				if (map[i][j] != 0) {
					tmp[idx++] = map[i][j];
					map[i][j] = 0;
				}
			}
			for (int i = N - 1; i >= N - idx; i--)
				map[i][j] = tmp[(N - 1) - i];
		}
	}
	else if (dir == 3) {
		for (int i = 0; i < N; i++) {
			idx = 0;
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0) {
					tmp[idx++] = map[i][j];
					map[i][j] = 0;
				}
			}
			for (int j = 0; j < idx; j++)
				map[i][j] = tmp[j];
		}
	}
}

//�������� ����� ��
void tilt_v(int dir, int row) {
	int ny;
	int y = row;

	if (dir == 0) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] == 0)continue;	//0�̸� ����ģ��.

			ny = y - 1;		//���� y��ǥ���� ����
			while (map[ny][x] == 0)
				ny -= 1;	//�տ� �ִ� ����� ã�´�.
			if (ny < 0)continue;

			//���� ������� ���� ����̰�, ���� ���� ���ٸ�
			if (map[ny][x] == map[y][x] && !visited[ny][x]) {
				map[y][x] = 0;
				map[ny][x] *= 2;
				visited[ny][x] = true;
			}
		}
	}
	else if (dir == 2) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] == 0)continue;

			ny = y + 1;
			while (map[ny][x] == 0)
				ny += 1;
			if (ny >= N)continue;
			if (map[ny][x] == map[y][x] && !visited[ny][x]) {
				map[y][x] = 0;
				map[ny][x] *= 2;
				visited[ny][x] = true;
			}
		}
	}
}

//�������� ����� ��
void tilt_h(int dir, int col) {
	int nx;
	int x = col;

	if (dir == 3) {
		for (int y = 0; y < N; y++) {
			if (map[y][x] == 0)continue;

			nx = x - 1;
			while (map[y][nx] == 0)
				nx -= 1;
			if (nx < 0)continue;
			if (map[y][nx] == map[y][x] && !visited[y][nx]) {
				map[y][x] = 0;
				map[y][nx] *= 2;
				visited[y][nx] = true;
			}
		}
	}
	else if (dir == 1) {
		for (int y = 0; y < N; y++) {
			if (map[y][x] == 0)continue;

			nx = x + 1;
			while (map[y][nx] == 0)
				nx += 1;
			if (nx >= N)continue;
			if (map[y][nx] == map[y][x] && !visited[y][nx]) {
				map[y][x] = 0;
				map[y][nx] *= 2;
				visited[y][nx] = true;
			}
		}
	}
}

void dfs(int cnt) {
	if (cnt >= 5) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				rst = max(rst, map[i][j]);
		return;
	}

	//���� dfs������ ���Ǵ� tmp��, �ٸ� dfs������ tmp�� �ߺ����� �ʴ´�.
	int tmp[MAX][MAX];
	memcpy(tmp, map, sizeof(tmp));

	//0: ��, 1: ��, 2: ��, 3: ��
	//��
	for (int i = 1; i < N; i++)
		tilt_v(0, i);		//1�� ~ N-1�� ������ ����
	arrange(0);				//����
	memset(visited, false, sizeof(visited));	//visit �ʱ�ȭ
	dfs(cnt + 1);			//���� dfs
	memcpy(map, tmp, sizeof(tmp));	//���� ���� ���� ���� map�� ���� ���·� �����.


									//��
	for (int i = N - 2; i >= 0; i--)
		tilt_h(1, i);
	arrange(1);
	memset(visited, false, sizeof(visited));
	dfs(cnt + 1);

	memcpy(map, tmp, sizeof(tmp));

	//��
	for (int i = N - 2; i >= 0; i--)
		tilt_v(2, i);
	arrange(2);
	memset(visited, false, sizeof(visited));
	dfs(cnt + 1);

	memcpy(map, tmp, sizeof(tmp));

	//��
	for (int i = 1; i < N; i++)
		tilt_h(3, i);
	arrange(3);
	memset(visited, false, sizeof(visited));
	dfs(cnt + 1);
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	dfs(0);
	cout << rst << endl;
	return 0;
}