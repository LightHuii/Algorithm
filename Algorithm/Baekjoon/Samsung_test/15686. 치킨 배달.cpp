#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
using namespace std;

#define MAX 51
int map[MAX][MAX] = { 0, };
vector<pair<int, int>>house;	//���� ��ǥ
int h_cnt;						//���� ����
vector<pair<int, int>>chstore;	//ġŲ���� ��ǥ
int ch_cnt;						//ġŰ���� ����
bool visited[MAX];
int N, M, rst = INT32_MAX;
int ary[13] = { 0, };		//���õ� ġŲ ���� idx ���� �迭

							//������ ġŲ  �Ÿ� ���� �Լ�
int chdist() {
	int rst = 0;

	//��� ���� ����
	for (int i = 0; i < h_cnt; i++) {
		//���õ� ġŲ ���鿡 ���� �ּ� ġŲ �Ÿ��� ����
		int mi = INT32_MAX;
		for (int j = 0; j < M; j++) {
			mi = min(mi, abs(chstore[ary[j]].first - house[i].first) + abs(chstore[ary[j]].second - house[i].second));
		}
		//��� ���ϰ� ����
		rst += mi;
	}

	return rst;
}

void dfs(int cnt, int idx) {
	//���õ� ġŲ���� ������ M�����
	if (cnt == M) {
		//������ ġŲ �Ÿ����Ͽ� �ּҰ� ���� �� ����
		rst = min(rst, chdist());
		return;
	}

	//ù ��° �õ����� 0�� °�� �����ؾ� �ϱ� ������ idx���� �ߺ����� üũ�ϱ�
	for (int i = idx; i < ch_cnt; i++) {
		if (visited[i])continue;
		visited[i] = true;
		ary[cnt] = i;

		dfs(cnt + 1, i);

		visited[i] = false;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				house.push_back(make_pair(i, j));
			else if (map[i][j] == 2)
				chstore.push_back(make_pair(i, j));
		}
	}

	h_cnt = house.size();
	ch_cnt = chstore.size();
	dfs(0, 0);

	cout << rst << endl;

	return 0;
}