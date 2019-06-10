#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 100
int map[MAX][MAX] = { 0, };
int T;

int main() {
	while (T < 10) {
		int y = 99, x;
		cin >> T;

		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				cin >> map[i][j];
				if (map[i][j] == 2)
					x = j;		
			}
		}
		for (int i = 1; i < MAX; i++) {
			//다음 좌표
			y = y - 1;	//북

			//서쪽
			if (x > 0 && map[y][x - 1] == 1) {
				x -= 1;
				while (x > 0 && map[y][x] == 1)
					x -= 1;
				//왼쪽 끝에 다다르면 그대로, 아니라면 1추가
				if (x > 0)
					x += 1;
			}
			//동쪽
			else if (x < 99 && map[y][x + 1] == 1) {
				x += 1;
				while (x < 99 && map[y][x] == 1)
					x += 1;
				//오른쪽 끝에 다다르면 그대로, 아니라면 1감소
				if (x < 99)
					x -= 1;
			}
		}

		cout << '#' << T << ' ' << x << endl;
	}

	return 0;
}