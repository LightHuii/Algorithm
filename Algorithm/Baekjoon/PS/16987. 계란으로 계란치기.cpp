#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 8
int N;
int egg[MAX][2];	//������, ����
int rst = 0;

void dfs(int idx, int cnt) {	//���� ��� ��ȣ, �� Ƚ��
	if (idx >= N) {		//���� ����
		rst = max(rst, cnt);
		return;
	}

	//���� ����� ������ �ʾҰ�, �� �� �ִ� ����� ���� ���� ��
	if (egg[idx][0] > 0 && cnt < N - 1) {
		//�� ��� ����
		for (int i = 0; i < N; i++) {
			if (i == idx || egg[i][0] <= 0)continue;

			//��� ����
			egg[idx][0] -= egg[i][1];
			egg[i][0] -= egg[idx][1];

			if (egg[idx][0] <= 0 && egg[i][0] <= 0)		//�� �� �����ٸ�
				dfs(idx + 1, cnt + 2);
			else if(egg[idx][0] <= 0 || egg[i][0] <= 0)	//�ϳ��� �����ٸ�
				dfs(idx + 1, cnt + 1);
			else										//�� �����ٸ�
				dfs(idx + 1, cnt);

			egg[idx][0] += egg[i][1];
			egg[i][0] += egg[idx][1];
		}
	}
	//���� ����� �����ų�, �� �� �ִ� ����� ���� ���� ���� ��
	else
		dfs(idx + 1, cnt);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> egg[i][0] >> egg[i][1];

	dfs(0, 0);
	cout << rst << endl;

	return 0;
}