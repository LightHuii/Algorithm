#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

#define MAX 1001
int C, N;
bool ary[MAX][MAX];
int gcd_rst[MAX][MAX];

int gcd(int a, int b) {
	if (a % b == 0)return b;
	return gcd(b, a % b);
}

int main()
{
	scanf("%d", &C);

	for (int i = 1; i <= 1000; i++) 
		for (int j = 1; j <= 1000; j++) 
			gcd_rst[i][j] = -1;

	//�̸� ��� ��ǥ�� ���� gcd�� ����� ���´�.
	for (int y = 1; y <= 1000; y++) {
		for (int x = 1; x <= y; x++) {
			gcd_rst[y][x] = gcd(y, x);
			gcd_rst[x][y] = gcd_rst[y][x];
		}
	}

	while (C--) {
		scanf("%d", &N);
		memset(ary, false, sizeof(ary));

		int cnt = 0;
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= y; x++) {
				if (gcd_rst[y][x] == 1)		//�ִ� ������� 1�� ��츸 �߰�
					cnt++;
			}
		}
		cnt++;
		cnt = cnt * 2 - 1;
		printf("%d\n", cnt);
	}

	return 0;
}