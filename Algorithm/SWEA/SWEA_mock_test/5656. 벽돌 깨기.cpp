#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

#define MAXY 15
#define MAXX 12
int T, N, W, H;
int map[MAXY][MAXX] = { 0, };
int rst = INT32_MAX;

void copy(int to[][MAXX], int from[][MAXX]) {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			to[i][j] = from[i][j];
}

void allign() {
	int tmp[MAXY][MAXX] = { 0, };

	for (int x = 0; x < W; x++) {
		int i = H - 1;
		for (int y = H - 1; y >= 0; y--) {
			if (map[y][x] == 0)continue;
			tmp[i--][x] = map[y][x];
		}
	}
	copy(map, tmp);
}

void bfs(int x) {
	queue< pair< int, pair< int, int >>>q;		//��, ��ǥ

												//x�� �ش��ϴ� ���� ã��
	int y = 0;
	while (map[y][x] == 0 && y < H)
		y++;
	q.push(make_pair(map[y][x], make_pair(y, x)));

	while (!q.empty()) {
		int val = q.front().first;
		int cy = q.front().second.first;
		int cx = q.front().second.second;
		q.pop();
		//if (cx < 0 || cx >= W)continue;
		//if (cy < 0 || cy >= H)continue;
		map[cy][cx] = 0;

		for (int j = cx - (val - 1); j < cx + val; j++) {
			int ny = cy;
			int nx = j;
			if (nx < 0 || nx >= W || nx == cx)continue;
			if (map[ny][nx] > 1)
				q.push(make_pair(map[ny][nx], make_pair(ny, nx)));
			map[ny][nx] = 0;
		}

		//����
		for (int j = cy - (val - 1); j < cy + val; j++) {
			int ny = j;
			int nx = cx;
			if (ny < 0 || ny >= H || ny == cy) continue;
			if (map[ny][nx] > 1)
				q.push(make_pair(map[ny][nx], make_pair(ny, nx)));
			map[ny][nx] = 0;
		}
	}
}

//���� ��ġ ����
void dfs(int cnt) {
	int tmp[MAXY][MAXX] = { 0, };
	copy(tmp, map);

	//������ ������ N���� �Ǹ� ����
	if (cnt == N) {

		//���� �� ����
		int rst_cnt = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (map[i][j] != 0)rst_cnt++;
			}
		}
		rst = min(rst, rst_cnt);

		return;
	}

	//���� �� �ƴٸ�
	//��� ����� �� ��������
	for (int i = 0; i < W; i++) {
		//����
		bfs(i);
		//����
		allign();
		//����
		dfs(cnt + 1);
		copy(map, tmp);
	}
}


int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {
		cin >> N >> W >> H;

		for (int i = 0; i < MAXY; i++) {
			for (int j = 0; j < MAXX; j++) {
				map[i][j] = 0;
			}
		}

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
			}
		}

		dfs(0);
		cout << '#' << T - Ttmp << ' ' << rst << endl;
		rst = INT32_MAX;
	}
}