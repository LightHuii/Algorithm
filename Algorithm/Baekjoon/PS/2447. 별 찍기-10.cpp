#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 7000
char map[MAX][MAX];
int N;

void func(int y, int x, int n) {
	//기저 조건
	if (n == 3) {
		for (int i = y; i < y + n; i++) {
			for (int j = x; j < x + n; j++) {
				if (i == y + 1 && j == x + 1)
					map[i][j] = '\0';
				else 
					map[i][j] = '*';
			}
		}

		return;
	}
	int tn = n / 3;
	func(y, x, n / 3);						//1
	func(y, x + tn, n / 3);					//2
	func(y, x + tn * 2, n / 3);				//3
	func(y + tn, x, n / 3);					//4
	func(y + tn, x + tn * 2, n / 3);		//5
	func(y + tn * 2, x, n / 3);				//6
	func(y + tn * 2, x + tn, n / 3);		//7
	func(y + tn * 2, x + tn * 2, n / 3);	//8
}

int main() {
	cin >> N;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			map[i][j] = '\0';

	if (N == 1)
		cout << '*' << endl;
	else {
		func(1, 1, N);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (map[i][j] == 0)cout << " ";
				else
					cout << map[i][j];
			}
			cout << endl;
		}
	}

	return 0;
}