#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 2048*3
int N;
char map[MAX][MAX];

void func(int n, int y, int x) {
	//기저 조건
	if (n == 3) {
		map[y][x] = '*';
		map[y + 1][x - 1] = '*';
		map[y + 1][x + 1] = '*';
		for (int j = x - 2; j <= x + 2; j++)
			map[y + 2][j] = '*';

		return;
	}

	//세 부분으로 나눠서 수행
	//꼭지점(y, x)부터 출력한다
	func(n / 2, y, x);
	func(n / 2, y + n / 2, x - n / 2);
	func(n / 2, y + n / 2, x + n / 2);
}

int main() {
	cin >> N;

	//공백으로 초기화
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			map[i][j] = ' ';

	//수행할 N의 값과 가장 큰 삼각형의
	func(N, 0, N - 1);

	//전체 출력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N * 2 - 1; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}

	return 0;
}