#include<iostream>
#include<algorithm>
using namespace std;

int N;
int cnt = 0;

int exponen(int n) {
	int tmp = 1;
	for (int i = 0; i < n; i++)
		tmp *= 2;
	return tmp;
}

//n��ŭ a���� b�� �̵�
void func(int n, int a, int b) {
	if (n == 1) {
		//a���� b�� �̵�
		printf("%d %d\n", a, b);
		return;
	}

	//c�� a �Ǵ� b�� �ƴ� ��
	int c = 6 - a - b;

	//�ϴ� n-1��ŭ a���� c�� �ű��
	func(n - 1, a, c);
	printf("%d %d\n", a, b);

	//�ٽ� n-1��ŭ c���� b�� �ű��
	func(n - 1, c, b);
}

int main() {
	scanf("%d", &N);

	if (N == 1)
		printf("%d\n", 1);
	else
		printf("%d\n", exponen(N) - 1);

	func(N, 1, 3);

	return 0;
}