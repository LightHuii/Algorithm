#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 50	//최대 이닝 수
int hitter[MAX][10];	//각 이닝에서 1~9번 타자의 결과
int ary[10];		//정해진 타자 순서
bool visited[10];	//타자 선택 체크
int N;
int rst = 0;		//결과 값

//모든 이닝이 끝날 때까지 경기 수행 및 결과 점수 리턴
int inning() {
	int order = 1, hitter_num;	//현재 타석 순서: 1~9, 순서에 대한 선수 번호
	int out_cnt = 0;	//아웃 개수
	bool base[4] = { 0, };	//1~3번 베이스에 있는 선수
	int inning_num = 0;	//현재 이닝 번호
	int score = 0;		//점수

	while (inning_num < N) {
		while (out_cnt < 3) {
			hitter_num = ary[order];	//현재 order의 타자 번호

			//아웃
			if (hitter[inning_num][hitter_num] == 0)
				out_cnt++;
			//안타
			else if (hitter[inning_num][hitter_num] == 1) {
				if (base[3]) {
					score++;
					base[3] = false;
				}
				base[3] = base[2];
				base[2] = base[1];
				base[1] = true;
			}
			//2루타
			else if (hitter[inning_num][hitter_num] == 2) {
				if (base[3]) {
					score++;
					base[3] = false;
				}
				if (base[2]) {
					score++;
					base[2] = false;
				}
				base[3] = base[1];
				base[1] = false;
				base[2] = true;
			}
			//3루타
			else if (hitter[inning_num][hitter_num] == 3) {
				if (base[3])
					score++;
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				base[3] = true;
			}
			//홈런
			else if (hitter[inning_num][hitter_num] == 4) {
				if (base[3]) {
					score++;
					base[3] = false;
				}
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				score++;
			}

			order = (order + 1) % 10;
			if (order == 0)order++;		//순서 증가
		}
		out_cnt = 0;
		for (int i = 1; i <= 3; i++)
			base[i] = false;

		inning_num++;	//다음 이닝
	}

	return score;
}

//타자 순서 정하기
void dfs(int cnt) {
	if (cnt >= 10) {
		int tmp = inning();
		rst = max(rst, tmp);
	
		return;
	}

	//4번 타자를 결정할 때
	if (cnt == 4)
		dfs(5);
	else {
		for (int i = 2; i <= 9; i++) {
			if (!visited[i]) {
				visited[i] = true;
				ary[cnt] = i;

				dfs(cnt + 1);

				visited[i] = false;
			}
		}
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 1; j <= 9; j++)
			cin >> hitter[i][j];

	//4번 째 선수는 1번 선수
	visited[1] = true;
	ary[4] = 1;

	dfs(1);

	cout << rst << endl;

	return 0;
}