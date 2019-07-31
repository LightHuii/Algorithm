#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 10
int A[MAX][MAX];
bool selected[MAX];
int order[4][20];		//지우, 경희, 민호의 정보
int N, K;
bool rst = false;

int func(int a, int b, int n1, int n2) {
	if (A[n1][n2] == 2)return a;
	else if (A[n1][n2] == 0)return b;
	//비겼을 때
	else {
		if (a < b)return b;
		else return a;
	}
}

//가위바위보 수행 결과 지우의 우승인지 아닌지 리턴
bool RPS() {
	int win_cnt[4] = { 0, };	//각 우승 횟수 저장 지우:1, 경희:2, 민호:3
	
	bool jiwoo = false;
	int do_cnt[4] = { 0, };		//각 가위바위보 순서 저장
	int won = 1;	//이전 승자 번호
	int next = 2;	//이전 승부에 참여하지 않은 사람의 번호

	//한 명이라도 승수를 모두 채우면 break
	while (1) {
		int winner = func(won, next, order[won][do_cnt[won]++], order[next][do_cnt[next]++]);
		win_cnt[winner]++;	//승자의 승수 증가

		//이번 승자가 승수를 채웠을 때
		if (win_cnt[winner] >= K) {
			if (winner == 1)jiwoo = true;	//우슨자가 지우라면
			break;
		}
		next = (won + next) % 4;
		if (next == 0)next = 2;
		won = winner;

		//지우의 순서가 끝났을 때
		if (do_cnt[1] >= N)break;
	}

	return jiwoo;
}

//지우의 순서를 정한 뒤, 가위바위보 수행하여 지우 우승여부 판단
void dfs(int cnt) {
	//이미 지우가 우승했으면, 더이상 진행하지 않는다
	if (rst)return;
	if (cnt >= N) {
		//가위바위보 수행하여 지우가 우승했는지 판단
		rst = RPS();
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (!selected[i]) {
			selected[i] = true;
			order[1][cnt] = i;
			dfs(cnt + 1);

			selected[i] = false;
		}
	}

}

int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> A[i][j];
	for (int i = 2; i <= 3; i++)
		for (int j = 0; j < 20; j++)
			cin >> order[i][j];
	
	dfs(0);
	cout << rst << endl;

	return 0;
}