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

//2^n * 2^n에 대해 y, x인 좌표를 찾는 함수, num은 y, x의 값을 의미
void func(int n, int y, int x, int num) {
	//이미 값을 찾았다면 리턴
	if (rst != -1)return;

	//기저 조건
	if (n == 0) {
		if (y == r && x == c)
			rst = num;
		return;
	}

	//다음 
	int ex = exponen(n - 1);
	int ex4 = exponen4(n - 1);

	//목적 좌표에 해당하는 부분만 선택적으로 탐색한다
	//다음 좌표에 해당하는 값은 4의 제곱에 비례한다
	//다음 좌표 자체는 2의 제곱만큼 증가한다
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