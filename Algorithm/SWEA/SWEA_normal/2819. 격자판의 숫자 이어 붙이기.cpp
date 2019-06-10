#include<iostream>
#include<algorithm>
#include<vector>
#include<memory.h>
using namespace std;

int T;
int map[4][4];
//7자리의 각 숫자가 존재하는지 판단하는 변수
int chk[10000000] = { 0, };
int rst;
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int Ttmp;

//이미 나왔던 값이면 true, 아니면 false 리턴
bool is_exist(int num) {

	//bool 대신 현재 테스트 케이스 값을 사용하여 초기화 과정을 생략할 수 있다.
	if (chk[num] != T - Ttmp) {
		chk[num] = T - Ttmp;
		return false;
	}
	else
		return true;
}

void dfs(int y, int x, int cnt, int num) {
	if (cnt == 6) {
		if (!is_exist(num))	//새롭게 나오늘 값이면 하나 증가시킨다.
			rst++;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4)continue;
		dfs(ny, nx, cnt + 1, 10 * num + map[ny][nx]);
	}
}

int main() {
	scanf("%d", &T);
	Ttmp = T;

	while (Ttmp--) {
		rst = 0;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				scanf("%1d", &map[i][j]);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				dfs(i, j, 0, map[i][j]);

		printf("#%d %d\n", T - Ttmp, rst);
	}
	return 0;
}