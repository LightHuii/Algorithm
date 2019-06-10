#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 64
char map[MAX][MAX];

int N;

//0�Ǵ� 1�� n*n�� ���� �� �ִ��� Ȯ���ϴ� �Լ�
//0���� ���� �� �ִٸ� 0, 1�� ���� �� �ִٸ� 1, �ƴ϶�� -1 ���
int check(int y, int x, int n) {
	bool flag0 = true;	//0Ȯ��
	bool flag1 = true;	//1Ȯ��

	for (int i = y; i < y + n; i++) {
		for (int j = x; j < x + n; j++) {
			if (map[i][j] == '1')
				flag0 = false;
			else
				flag1 = false;
		}
	}

	if (flag0)
		return 0;
	else if (flag1)
		return 1;
	else
		return -1;
}

//y, x���� n���� ���� �� ������ �ش� ���ڷ� ���,
//�ƴ϶�� 4����Ͽ� �� ������ ������ ����� ���
void func(int n, int y, int x) {
	if (n == 1) {
		cout << map[y][x];
		return;
	}

	int chk = check(y, x, n);
	
	//0 �Ǵ� 1�� ������ �� �ִٸ� �ٷ� ����Ѵ�.
	if (chk == 0)
		cout << '0';
	else if (chk == 1)
		cout << '1';
	//�ƴ϶��, �ش� ������ 4����Ͽ� ������� �����Ѵ�.
	else {
		cout << '(';
		func(n / 2, y, x);
		func(n / 2, y, x + n / 2);
		func(n / 2, y + n / 2, x);
		func(n / 2, y + n / 2, x + n / 2);
		cout << ')';
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	func(N, 0, 0);

	return 0;
}