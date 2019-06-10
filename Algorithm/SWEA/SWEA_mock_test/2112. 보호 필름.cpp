#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

int T, D, W, K;
int map[13][20];
int rst;

bool judge() {
	int flag;
	for (int j = 0; j < W; j++) {
		for (int i = 0; i <= D - K; i++) {

			//0일 때
			if (map[i][j] == 0) {
				flag = 0;
				//전부 0이여야 함
				for (int k = 1; k < K; k++)
					flag |= map[i + k][j];

				//마지막 이전에 틀렸다면, 다음 행으로 가서 다시 시작
				if (flag == 1 && i < D - K) continue;
				//마지막에 틀렸다면, 전체가 틀린 경우
				else if (flag == 1 && i == D - K)
					return false;
				//맞다면, 다음 열로 이동
				else if (flag == 0)
					break;
			}
			//1일 때
			else {
				flag = 1;
				for (int k = 1; k < K; k++)
					flag &= map[i + k][j];

				if (flag == 0 && i < D - K) continue;
				else if (flag == 0 && i == D - K)
					return false;
				else if (flag == 1)
					break;
			}
		}
	}
	return true;
}

void fill_ary(int row, int ab) {
	for (int i = 0; i < W; i++)
		map[row][i] = ab;
}

void dfs(int cnt, int row) {
	if (judge()) {
		rst = min(rst, cnt);
		return;
	}

	if (cnt > K || row >= D)return;


	int tmp[20];
	memcpy(tmp, map + row, sizeof(int)*W);

	//row 층에 A 투입
	fill_ary(row, 0);
	dfs(cnt + 1, row + 1);

	memcpy(map + row, tmp, sizeof(int)*W);

	//row 층에 B 투입
	fill_ary(row, 1);
	dfs(cnt + 1, row + 1);

	memcpy(map + row, tmp, sizeof(int)*W);

	//아무것도 하지 않고 다음
	dfs(cnt, row + 1);
}

int main() {
	int Ttmp;
	cin >> T;
	Ttmp = T;

	while (Ttmp--) {
		cin >> D >> W >> K;
		for (int i = 0; i < D; i++)
			for (int j = 0; j < W; j++)
				cin >> map[i][j];

		rst = INT32_MAX;
		if (judge() || K == 1)
			rst = 0;
		else
			dfs(0, 0);
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}
	return 0;
}