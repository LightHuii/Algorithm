#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

int N, r, c;
int rst = -1;

//2^n
int exponen(int n) {
	int tmp = 1;
	for (int i = 0; i < n; i++)
		tmp *= 2;
	return tmp;
}

//4^n
int exponen4(int n) {
	int tmp = 1;
	for (int i = 0; i < n; i++)
		tmp *= 4;
	return tmp;
}

//2^n * 2^n�� ���� y, x�� ��ǥ�� ã�� �Լ�, num�� y, x�� ���� �ǹ�
void func(int n, int y, int x, int num) {
	//�̹� ���� ã�Ҵٸ� ����
	if (rst != -1)return;

	//���� ����
	if (n == 0) {
		if (y == r && x == c)
			rst = num;
		return;
	}

	//���� 
	int ex = exponen(n - 1);
	int ex4 = exponen4(n - 1);

	//���� ��ǥ�� �ش��ϴ� �κи� ���������� Ž���Ѵ�
	//���� ��ǥ�� �ش��ϴ� ���� 4�� ������ ����Ѵ�
	//���� ��ǥ ��ü�� 2�� ������ŭ �����Ѵ�
	if (r >= y && r < y + ex && c >= x && c < x + ex)
		func(n - 1, y, x, num);
	if (r >= y && r < y + ex && c >= x + ex && c < x + ex * 2)
		func(n - 1, y, x + ex, num + ex4);
	if (r >= y + ex && r < y + ex * 2 && c >= x && c < x + ex)
		func(n - 1, y + ex, x, num + 2 * ex4);
	if (r >= y + ex && r < y + ex * 2 && c >= x + ex && c < x + ex * 2)
		func(n - 1, y + ex, x + ex, num + 3 * ex4);
}

int main() {
	cin >> N >> r >> c;

	func(N, 0, 0, 0);

	cout << rst << endl;
	return 0;
}