#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define MAX 10
int rst = 0;
int N;
bool selected[MAX];		//n개의 재료 선택 여부
pair<int, char>material[MAX][4][4];		//재료 내용
pair<int, char>pot[5][5];

//마지막 가마의 결과값 출력
int final_pot() {
	int r = 0, b = 0, g = 0, y = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (pot[i][j].second == 'R')
				r += pot[i][j].first;
			else if (pot[i][j].second == 'B')
				b += pot[i][j].first;
			else if (pot[i][j].second == 'G')
				g += pot[i][j].first;
			else if (pot[i][j].second == 'Y')
				y += pot[i][j].first;
		}
	}

	return 7 * r + 5 * b + 3 * g + 2 * y;
}

//재료를 덮기
//재료 번호, 회전 방향: 0,1,2,3 (그대로, 시계, 반시계, 2번), 위치 (0, 0),(0, 1),(1, 0),(1, 1) 
void take_mat(int n, int dir, int loc) {
	pair<int, char>mattmp[4][4];

	//사용할 재료 배열 mattmp 확보
	//회전
	if (dir == 0) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mattmp[i][j] = material[n][i][j];
	}
	else if (dir == 1) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mattmp[j][3 - i] = material[n][i][j];
	}
	else if (dir == 2) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mattmp[3 - j][i] = material[n][i][j];
	}

	//offset
	int dy, dx;
	if (loc == 0) {
		dy = 0;
		dx = 0;
	}
	else if (loc == 1) {
		dy = 0;
		dx = 1;
	}
	else if (loc == 2) {
		dy = 1;
		dx = 0;
	}
	else if (loc == 3) {
		dy = 1;
		dx = 1;
	}

	//덮기
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//수 더하기
			pot[i + dy][j + dx].first += mattmp[i][j].first;

			if (pot[i + dy][j + dx].first < 0)
				pot[i + dy][j + dx].first = 0;
			else if (pot[i + dy][j + dx].first > 9)
				pot[i + dy][j + dx].first = 9;

			//색깔 바꾸기
			if (mattmp[i][j].second != 'W')
				pot[i + dy][j + dx].second = mattmp[i][j].second;
		}
	}
}

void dfs(int cnt) {
	if (cnt == 3) {
		//rst의 최대값 확인

		rst = max(rst, final_pot());
		return;
	}

	//재료 0 ~ N-1까지
	for (int i = 0; i < N; i++) {
		if (!selected[i]) {
			selected[i] = true;

			//i에 대해 수행: 회전, 위치까지
			for (int d = 0; d < 3; d++) {
				for (int l = 0; l < 4; l++) {
					//pot 백업
					pair<int, char>pottmp[5][5];
					memcpy(pottmp, pot, sizeof(pot));

					take_mat(i, d, l);
					dfs(cnt + 1);

					memcpy(pot, pottmp, sizeof(pot));
				}
			}
			selected[i] = false;
		}
	}
}

int main() {
	cin >> N;

	for (int n = 0; n < N; n++) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cin >> material[n][i][j].first;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cin >> material[n][i][j].second;
	}

	//초기화
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			pot[i][j].first = 0;
			pot[i][j].second = 'W';
		}
	}

	dfs(0);

	cout << rst << endl;

	return 0;
}