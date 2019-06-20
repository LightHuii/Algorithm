#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 1000
int dp[MAX] = { 0, };
int ary[MAX];
int N;

//dp[i]: i�� ���Ե� �κ� ���� ���� �� ���� �� ����

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> ary[i];

	int rst = 1;		//�κ� �������� ���� �� ���� �� ��
	dp[0] = 1;

	for (int i = 1; i < N; i++) {
		int idx = i - 1;

		//���纸�� �۰�, dp�� ���� ū ��ǥ�� 0 ~ i-1���� ã�´�
		int tmp = 0;
		for (int j = 0; j < i; j++) {
			if (ary[j] < ary[i])
				tmp = max(tmp, dp[j]);
		}

		dp[i] = tmp + 1;
		rst = max(dp[i], rst);
	}
	cout << rst << endl;

	return 0;
}