#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<vector<pair<int, int>>>v;
int dy[] = { 0, -1, 0, 1 };
int dx[] = { 1, 0, -1, 0 };
int map[101][101] = { 0, };

int main() {
	int N, x, y, d, g;
	pair<int, int>cri;
	cin >> N;

	v.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		v[i].push_back(make_pair(x, y));
		cri = make_pair(x + dx[d], y + dy[d]);
		v[i].push_back(cri);

		//���� �ݺ�
		for (int j = 0; j < g; j++) {
			//������ ������ ������ ��ǥ�� ����
			int tx, ty;
			int size = v[i].size();
			for (int k = size - 2; k >= 0; k--) {
				//�ð� ���� 90�� ����
				tx = -1 * (cri.second - v[i][k].second);
				ty = cri.first - v[i][k].first;
				tx = cri.first - tx;
				ty = cri.second - ty;

				v[i].push_back(make_pair(tx, ty));
			}
			cri = make_pair(tx, ty);	//���������� �� ��ǥ�� ���� ����
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < (int)v[i].size(); j++) {
			int tx = v[i][j].first;
			int ty = v[i][j].second;
			map[tx][ty] = 1;
		}
	}

	//�簢�� ���� ����
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
				cnt++;
		}
	}

	cout << cnt << endl;

	return 0;
}