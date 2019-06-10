#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 64
char map[MAX][MAX];

int N;

//0또는 1로 n*n을 덮을 수 있는지 확인하는 함수
//0으로 덮을 수 있다면 0, 1로 덮을 수 있다면 1, 아니라면 -1 출력
int check(int y, int x, int n) {
	bool flag0 = true;	//0확인
	bool flag1 = true;	//1확인

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

//y, x부터 n까지 덮을 수 있으면 해당 숫자로 출력,
//아니라면 4등분하여 각 영역을 압축한 결과를 출력
void func(int n, int y, int x) {
	if (n == 1) {
		cout << map[y][x];
		return;
	}

	int chk = check(y, x, n);
	
	//0 또는 1로 압출학 수 있다면 바로 출력한다.
	if (chk == 0)
		cout << '0';
	else if (chk == 1)
		cout << '1';
	//아니라면, 해당 영역을 4등분하여 순서대로 수행한다.
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