#include <iostream>
#include <algorithm>
#include <string>
#include <memory.h>
using namespace std;

#define MAX 10
#define NUM(y, x) (((y - 1) / 3) * 3 + ((x - 1) / 3) + 1)
#define CAN_SET(y, x, n) (!ver[x][n] && !hor[y][n] && !cell[NUM(y, x)][n])
int map[MAX][MAX] = { 0, };
bool ver[MAX][MAX];		//열 체크
bool hor[MAX][MAX];		//행 체크
bool cell[MAX][MAX];	//3*3 단위 격자 체크
bool domino[MAX][MAX];		//도미노 조합 체크
int dy[] = { 1, 0 };	
int dx[] = { 0, 1 };
int N;
bool flag;
int puzzle_cnt = 1;

void init() {
	memset(map, 0, sizeof(map));
	memset(ver, false, sizeof(ver));
	memset(hor, false, sizeof(hor));
	memset(cell, false, sizeof(cell));
	memset(domino, false, sizeof(domino));
	flag = false;
}

//도미노 놓기
void set_domi(int y, int x, int n) {
	map[y][x] = n;
	ver[x][n] = true;
	hor[y][n] = true;
	cell[NUM(y, x)][n] = true;
}

//도미도 제거
void unset_domi(int y, int x, int n) {
	map[y][x] = 0;
	ver[x][n] = false;
	hor[y][n] = false;
	cell[NUM(y, x)][n] = false;
}

void dfs(int y, int x, int cnt) {
	//이미 답이 나왔을 경우 
	if (flag)return;

	//좌표가 끝까지 왔다면
	if (y >= 10) {
		//놓을 수 있는 도미노는 전부 놓았을 때
		if (cnt == 36 - N) {
			//출력
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					cout << map[i][j];
				}
				cout << endl;
			}

			flag = true;	//이미 정답이 나왔다고 표시
			return;
		}
		return;
	}
	//놓을 수 있는 도미노의 수보다 더 많이 놓을 경우 제거
	if (cnt > 36 - N)return;

	//다음 좌표
	int ny = y, nx = x + 1;
	if (nx >= 10) {
		nx = 1;
		ny++;
	}

	//현재 자리가 비어있다면
	if (map[y][x] == 0) {
		for (int i = 1; i <= 9; i++) {
			//첫 번째 숫자 판단
			if (!CAN_SET(y, x, i)) continue;	//놓을 수 없다면
			//첫 번째 놓기
			set_domi(y, x, i);

			for (int j = 1; j <= 9; j++) {
				if (i == j || domino[i][j] || domino[j][i])continue;
				domino[i][j] = true;
				domino[j][i] = true;

				//두 번째 숫자 판단
				for (int k = 0; k < 2; k++) {
					int sy = y + dy[k];
					int sx = x + dx[k];
					if (sy < 1 || sy > 9 || sx < 1 || sx > 9)continue;
					//놓을 수 없다면
					if (map[sy][sx] != 0 || !CAN_SET(sy, sx, j))continue;
					//두 번째 놓기
					set_domi(sy, sx, j);

					//다음으로
					dfs(ny, nx, cnt + 1);

					//두 번째 해제
					unset_domi(sy, sx, j);
				}
				domino[i][j] = false;
				domino[j][i] = false;
			}

			//첫 번째 해제
			unset_domi(y, x, i);
		}
	}
	//아니라면 다음 좌표로
	else
		dfs(ny, nx, cnt);
}

int main()
{
	while (1) {
		cin >> N;
		if (N == 0)break;

		//초기화
		init();

		//입력 및 체크
		for (int i = 0; i < N; i++) {
			string str;
			int n1, n2, y, x;

			cin >> n1 >> str;
			y = (int)(str[0] - 'A' + 1);
			x = (int)(str[1] - '0');
			set_domi(y, x, n1);

			cin >> n2 >> str;
			y = (int)(str[0] - 'A' + 1);
			x = (int)(str[1] - '0');
			set_domi(y, x, n2);

			domino[n1][n2] = true;
			domino[n2][n1] = true;
		}

		for (int i = 1; i <= 9; i++) {
			string str;
			int y, x;
			cin >> str;
			y = (int)(str[0] - 'A' + 1);
			x = (int)(str[1] - '0');
			set_domi(y, x, i);
		}

		cout << "Puzzle " << puzzle_cnt++ << endl;
		dfs(1, 1, 0);	//(1, 1)부터 시작하고, 도미노를 하나도 놓지 않았다면
	}

	return 0;
}