#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef struct tmp {
	int y, x;
}mp;

#define MAX 20010
bool map[5][MAX];
int rst[MAX];
string str;
int N, len, cnt = 0;

//1인지 판단
bool isone(int x) {
	//1열을 차지하는가
	for (int i = 0; i < 5; i++) {
		if (!map[i][x])
			return false;
	}
	//오른쪽 열이 비어 있는가
	if (x < (N / 5 - 1)) {
		for (int i = 0; i < 5; i++) {
			if (map[i][x + 1])
				return false;
		}
	}
	//왼쪽 열이 비어 있는가
	if (x > 0) {
		for (int i = 0; i < 5; i++) {
			if (map[i][x - 1])
				return false;
		}
	}
	return true;
}

int main(void)
{
	cin >> N;
	cin >> str;

	//map이라는 배열로 옮긴다
	int idx = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < N / 5; j++) {
			if (str[idx++] == '#')
				map[i][j] = true;
		}
	}

	//x좌표에 따라 '#'라면 숫자를 만족하는지 검사
	for (int x = 0; x < N / 5; x++) {
		//비어있다면 넘어가기
		if (!map[0][x])continue;
		//1먼저 검사
		if (isone(x)) {
			rst[cnt++] = 1;
			x++;
			continue;
		}

		//각 개수 검사를 통해 7, 9, 11, 12, 13개로 나눌 수 있다.
		int ncnt = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = x; j < x + 3; j++) {
				if (map[i][j])
					ncnt++;
			}
		}

		switch (ncnt)
		{
		//4
		case 9:
			rst[cnt] = 4;
			break;
		//2, 3, 5
		case 11:
			if (!map[3][x + 2])rst[cnt] = 2;
			else if (!map[1][x] && !map[3][x])rst[cnt] = 3;
			else if (!map[1][x + 2])rst[cnt] = 5;
			break;
		//6, 9
		case 12:
			if (!map[1][x + 2])rst[cnt] = 6;
			else if (!map[3][x])rst[cnt] = 9;
			break;
		//8
		case 13:
			rst[cnt] = 8;
			break;
		//7
		case 7:
			rst[cnt] = 7;
			break;
		default:
			break;
		}
		cnt++;
		x += 2;	//공백을 넘기고 바로 다음 숫자 판단
	}

	for (int i = 0; i < cnt; i++)
		cout << rst[i];
	cout << endl;

	return 0;
}