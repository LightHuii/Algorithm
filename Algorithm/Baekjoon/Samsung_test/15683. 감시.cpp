#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>
using namespace std;

#define MAX 8
int map[MAX][MAX];
int N, M;
int rst = MAX*MAX;
int cctv_cnt = 0;
vector<pair<int, pair<int, int>>>cctv;	//cctv����, ��ǥ

										//cctv�� ���� üũ
void check(int y, int x, int dir) {
	switch (dir)
	{
		//��
	case 0:
		for (int i = y - 1; i >= 0; i--) {
			if (map[i][x] == 6)break;
			if (map[i][x] == 0)map[i][x] = -1;
		}
		break;
		//��
	case 1:
		for (int i = x + 1; i < M; i++) {
			if (map[y][i] == 6)break;
			if (map[y][i] == 0)map[y][i] = -1;
		}
		break;

		//��
	case 2:
		for (int i = y + 1; i < N; i++) {
			if (map[i][x] == 6)break;
			if (map[i][x] == 0)map[i][x] = -1;
		}
		break;
		//��
	case 3:
		for (int i = x - 1; i >= 0; i--) {
			if (map[y][i] == 6)break;
			if (map[y][i] == 0)map[y][i] = -1;
		}
		break;
	default:
		break;
	}
}

void dfs(int idx) {
	//��� cctv�� Ž���ߴٸ�
	//���� ����, ����
	if (idx == cctv_cnt) {
		int tmp = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (map[i][j] == 0)tmp++;
		rst = min(rst, tmp);
		return;
	}

	//�ӽ÷� ���� ���� ������ �迭
	int tmp_map[MAX][MAX];
	memcpy(tmp_map, map, sizeof(map));

	//���� ��ǥ�� cctv ����
	int y = cctv[idx].second.first;
	int x = cctv[idx].second.second;
	int num = cctv[idx].first;

	//���� cctv�� ���� �þ߸� üũ�ϰ�, ���� cctv�� �Ѿ
	switch (num)
	{
	case 1:
		for (int i = 0; i < 4; i++) {
			check(y, x, i);
			dfs(idx + 1);
			memcpy(map, tmp_map, sizeof(map));
		}
		break;
	case 2:
		for (int i = 0; i < 2; i++) {
			check(y, x, i);
			check(y, x, i + 2);
			dfs(idx + 1);
			memcpy(map, tmp_map, sizeof(map));
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++) {
			check(y, x, i);
			check(y, x, (i + 1) % 4);
			dfs(idx + 1);
			memcpy(map, tmp_map, sizeof(map));
		}
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			check(y, x, i);
			check(y, x, (i + 1) % 4);
			check(y, x, (i + 3) % 4);
			dfs(idx + 1);
			memcpy(map, tmp_map, sizeof(map));
		}
		break;
	case 5:
		check(y, x, 0);
		check(y, x, 1);
		check(y, x, 2);
		check(y, x, 3);
		dfs(idx + 1);
		memcpy(map, tmp_map, sizeof(map));
		break;
	default:
		break;
	}

}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] >= 1 && map[i][j] <= 5) {
				cctv_cnt++;
				cctv.push_back(make_pair(map[i][j], make_pair(i, j)));
			}
		}
	}
	dfs(0);

	cout << rst << endl;
	return 0;
}