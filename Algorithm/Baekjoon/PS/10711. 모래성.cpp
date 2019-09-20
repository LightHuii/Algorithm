#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 1001
int H, W;
char map[MAX][MAX];
int dy[] = { 0,0,-1,1,-1,1,-1,1 };
int dx[] = { -1,1,0,0,-1,1,1,-1 };
int scount[MAX][MAX] = { 0, };
int t = 0;
vector<pair<int, int>>v1;
vector<pair<int, int>>v2;

int main()
{
	cin >> H >> W;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
		}
	}

	bool flag1 = false;		//ó�� ������ �� �� �ϳ��� �������ٸ� true

	//�ܼ� Ž������ �ֺ�'.'�� ������ ����, �������� ��ǥ�� �ִٸ� push
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] == '.')continue;
			for (int k = 0; k < 8; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
				if (map[ny][nx] == '.') {
					scount[i][j]++;
					if (scount[i][j] == map[i][j] - '0') {
						v1.push_back(make_pair(i, j));
						flag1 = true;
					}
				}
			}
		}
	}

	while (flag1) {
		bool flag2 = false;		//�� ���̶� �������ٸ� true

		//������ �������� ��ǥ:v1
		//������ �������� ��ǥ�� '.'�� �ǰ�, �ֺ� ��ǥ�� ī��Ʈ�� ������Ų��.
		for (int i = 0; i < (int)v1.size(); i++) {
			int y = v1[i].first;
			int x = v1[i].second;

			for (int j = 0; j < 8; j++) {
				int ny = y + dy[j];
				int nx = x + dx[j];
				if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
				if (map[ny][nx] == '.')continue;
				
				//�ֺ� '.'�� �ƴ� ��ǥ�� ����
				scount[ny][nx]++;
				//���� ������ ���� v2�� push�Ѵ� 
				if (map[ny][nx] - '0' == scount[ny][nx]) {
					v2.push_back(make_pair(ny, nx));
					flag2 = true;
				}
			}
		}
		v1.clear();

		//v2�� ����
		for (int i = 0; i < (int)v2.size(); i++)
			v1.push_back(v2[i]);
		v2.clear();

		t++;
		if (!flag2)break;

	}

	cout << t << endl;

	return 0;
}