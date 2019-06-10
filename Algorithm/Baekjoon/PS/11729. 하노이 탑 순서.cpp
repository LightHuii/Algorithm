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

//n만큼 a에서 b로 이동
void func(int n, int a, int b) {
	if (n == 1) {
		//a에서 b로 이동
		printf("%d %d\n", a, b);
		return;
	}

	//c는 a 또는 b가 아닌 수
	int c = 6 - a - b;

	//일단 n-1만큼 a에서 c로 옮긴다
	func(n - 1, a, c);
	printf("%d %d\n", a, b);

	//다시 n-1만큼 c에서 b로 옮긴다
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