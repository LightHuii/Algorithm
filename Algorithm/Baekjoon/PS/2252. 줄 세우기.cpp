#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 32001
int N, M;
int cnt[MAX] = { 0, };		//�ڽ����� ������ ������ ����
vector<vector<int>>v;

int main()
{
	int a, b;
	cin >> N >> M;
	v.resize(N + 1);

	//��带 ���ϴ� ������ ���� üũ
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cnt[b]++;
		v[a].push_back(b);
	}

	int mi, idx = 0;
	for (int i = 1; i <= N; i++) {
		mi = INT32_MAX;

		//�ּҰ� ã��
		for (int j = 1; j <= N; j++) {
			if (mi > cnt[j]) {
				mi = cnt[j];
				idx = j;
			}
		}

		//���� ���� ����� ��ȣ ���
		cout << idx << ' ';
		cnt[idx] = INT32_MAX;

		//����� �����  cnt ����
		for (int j = 0; j < (int)v[idx].size(); j++) {
			int next = v[idx][j];
			cnt[next]--;
		}
		v[idx].clear();
	}


	return 0;
}
