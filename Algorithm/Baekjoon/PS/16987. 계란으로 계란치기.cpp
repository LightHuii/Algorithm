#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 8
int N;
int egg[MAX][2];	//내구도, 무게
int rst = 0;

void dfs(int idx, int cnt) {	//현재 계란 번호, 깬 횟수
	if (idx >= N) {		//종료 조건
		rst = max(rst, cnt);
		return;
	}

	//현재 계란이 깨지지 않았고, 깰 수 있는 계란이 남아 있을 때
	if (egg[idx][0] > 0 && cnt < N - 1) {
		//깰 계란 선택
		for (int i = 0; i < N; i++) {
			if (i == idx || egg[i][0] <= 0)continue;

			//계란 깨기
			egg[idx][0] -= egg[i][1];
			egg[i][0] -= egg[idx][1];

			if (egg[idx][0] <= 0 && egg[i][0] <= 0)		//둘 다 깨졌다면
				dfs(idx + 1, cnt + 2);
			else if(egg[idx][0] <= 0 || egg[i][0] <= 0)	//하나만 깨졌다면
				dfs(idx + 1, cnt + 1);
			else										//안 깨졌다면
				dfs(idx + 1, cnt);

			egg[idx][0] += egg[i][1];
			egg[i][0] += egg[idx][1];
		}
	}
	//현재 계란이 깨졌거나, 깰 수 있는 계란이 남아 있지 않을 때
	else
		dfs(idx + 1, cnt);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> egg[i][0] >> egg[i][1];

	dfs(0, 0);
	cout << rst << endl;

	return 0;
}