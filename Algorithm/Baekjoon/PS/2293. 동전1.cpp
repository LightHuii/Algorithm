#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define NMAX 100
#define KMAX 10001
int n, k;
int dp1[KMAX] = { 0, };		//���� dp �迭
int dp2[KMAX] = { 0, };		//���� dp �迭
int coin[NMAX];

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> coin[i];

	//0���� ù ������ ����� ��� 1������� ���Ѵ�.
	for (int i = 0; i <= k; i += coin[0])
		dp1[i] = 1;

	int cidx = 1;	//����� ������ index

	while (cidx < n) {
		memset(dp2, 0, sizeof(dp2));		//dp2 �ʱ�ȭ

		for (int i = 0; i <= k; i++) {
			//�ϴ� dp2�� dp1�� ����(���� �� �����ϹǷ�)
			dp2[i] = dp1[i];

			//���� ���� ���� ������� �ϴ� ������ ���ų� �۴ٸ�
			if (coin[cidx] <= i)
				dp2[i] += dp2[i - coin[cidx]];	//���� dp�� �����ش�
		}

		//���� ���ʸ� ���ؼ� dp1�� dp2�� ����
		for (int i = 0; i <= k; i++)
			dp1[i] = dp2[i];
		
		cidx++;	//������ �ε��� ����
	}

	cout << dp1[k] << endl;	//n�� 1�� ��� dp2�� ��� 0�̹Ƿ� dp1 ����

	return 0;
}