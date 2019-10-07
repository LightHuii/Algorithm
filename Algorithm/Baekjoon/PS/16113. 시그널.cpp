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

//1���� �Ǵ�
bool isone(int x) {
	//1���� �����ϴ°�
	for (int i = 0; i < 5; i++) {
		if (!map[i][x])
			return false;
	}
	//������ ���� ��� �ִ°�
	if (x < (N / 5 - 1)) {
		for (int i = 0; i < 5; i++) {
			if (map[i][x + 1])
				return false;
		}
	}
	//���� ���� ��� �ִ°�
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

	//map�̶�� �迭�� �ű��
	int idx = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < N / 5; j++) {
			if (str[idx++] == '#')
				map[i][j] = true;
		}
	}

	//x��ǥ�� ���� '#'��� ���ڸ� �����ϴ��� �˻�
	for (int x = 0; x < N / 5; x++) {
		//����ִٸ� �Ѿ��
		if (!map[0][x])continue;
		//1���� �˻�
		if (isone(x)) {
			rst[cnt++] = 1;
			x++;
			continue;
		}

		//�� ���� �˻縦 ���� 7, 9, 11, 12, 13���� ���� �� �ִ�.
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
		x += 2;	//������ �ѱ�� �ٷ� ���� ���� �Ǵ�
	}

	for (int i = 0; i < cnt; i++)
		cout << rst[i];
	cout << endl;

	return 0;
}