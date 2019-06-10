#include<iostream>
#include<algorithm>
#include<memory.h>
#include<math.h>
using namespace std;

#define MAX 16
int S[MAX][MAX];
bool selected[MAX];
int T, N;
int rst;

void dfs(int cnt, int idx) {
	if (cnt == N / 2) {
		//실행
		int a = 0, b = 0;	//시너지들의 합

		for (int i = 0; i < N; i++) {
			//음식1의 재료들끼리
			if (selected[i]) {
				for (int j = 0; j < N; j++) {
					if (i == j)continue;
					if (selected[j])
						a += S[i][j];
				}
			}
			//음식2의 재료들끼리
			else {
				for (int j = 0; j < N; j++) {
					if (i == j)continue;
					if (!selected[j])
						b += S[i][j];
				}
			}
		}
		rst = min(rst, abs(a - b));

		return;
	}
	if (idx >= N)return;

	//idx부터 생각하여, 중복을 없앰
	for (int i = idx; i < N - 1; i++) {
		if (!selected[i]) {
			selected[i] = true;
			dfs(cnt + 1, i + 1);
			selected[i] = false;
		}
	}
}

int main() {
	cin >> T;
	int Ttmp = T;

	while (Ttmp--) {
		cin >> N;

		//초기화
		memset(selected, false, sizeof(selected));
		rst = INT32_MAX;

		//시너지 입력
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> S[i][j];

		dfs(0, 0);
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}
​