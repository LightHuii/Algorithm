#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 2048*3
int N;
char map[MAX][MAX];

void func(int n, int y, int x) {
	//���� ����
	if (n == 3) {
		map[y][x] = '*';
		map[y + 1][x - 1] = '*';
		map[y + 1][x + 1] = '*';
		for (int j = x - 2; j <= x + 2; j++)
			map[y + 2][j] = '*';

		return;
	}

	//�� �κ����� ������ ����
	//������(y, x)���� ����Ѵ�
	func(n / 2, y, x);
	func(n / 2, y + n / 2, x - n / 2);
	func(n / 2, y + n / 2, x + n / 2);
}

int main() {
	cin >> N;

	//�������� �ʱ�ȭ
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			map[i][j] = ' ';

	//������ N�� ���� ���� ū �ﰢ����
	func(N, 0, N - 1);

	//��ü ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N * 2 - 1; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}

	return 0;
}