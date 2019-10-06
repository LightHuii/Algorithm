#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int ary[4][6][3];
int rst[4];					//��� ����
int tmp[6][3] = { 0, };		//�ӽ� ��, ��, �� ǥ
bool flag;

void dfs(int order, int num, int idx) {
	if (flag) return;

	//���� ����
	if (num >= 6) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				if (ary[order][i][j] != tmp[i][j])
					return;
			}
		}

		flag = true;
		return;
	}

	//���� ����� �Ѿ�� �� ���
	if (idx >= 6)
		dfs(order, num + 1, num + 2);
	else {
		//num�� idx�� �̱� �� �ִ� ���
		if (tmp[num][0] < ary[order][num][0] && tmp[idx][2] < ary[order][idx][2]) {
			tmp[num][0]++;
			tmp[idx][2]++;
			dfs(order, num, idx + 1);
			tmp[num][0]--;
			tmp[idx][2]--;
		}
		//num�� idx�� �� ���
		if (tmp[num][2] < ary[order][num][2] && tmp[idx][0] < ary[order][idx][0]) {
			tmp[num][2]++;
			tmp[idx][0]++;
			dfs(order, num, idx + 1);
			tmp[num][2]--;
			tmp[idx][0]--;
		}
		//num�� idx�� ��� ���
		if (tmp[num][1] < ary[order][num][1] && tmp[idx][1] < ary[order][idx][1]) {
			tmp[num][1]++;
			tmp[idx][1]++;
			dfs(order, num, idx + 1);
			tmp[num][1]--;
			tmp[idx][1]--;
		}
	}
}

int main(void)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++)
			for (int l = 0; l < 3; l++)
				cin >> ary[i][j][l];

	for (int i = 0; i < 4; i++) {
		flag = false;
		memset(tmp, 0, sizeof(tmp));
		dfs(i, 0, 1);

		if (flag)
			rst[i] = 1;
		else
			rst[i] = 0;
	}

	for (int i = 0; i < 4; i++)
		cout << rst[i] << ' ';
	cout << endl;

	return 0;
}