#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

int T, N, M, K, A, B;
int person[1000];
int window1[20][3], window2[20][3];		//[0]: 필요한 처리시간, [1]: 현재 진행 시간, [2]: 처리중인 사람num
int used[1000][2];		//[0]: 접수 창구 번호, [1]: 정비 창구 번호

int main() {
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		memset(window1, 0, sizeof(window1));
		memset(window2, 0, sizeof(window2));
		memset(used, 0, sizeof(used));
		queue<int>wait2;
		priority_queue<int>wait1;

		cin >> N >> M >> K >> A >> B;
		for (int i = 0; i < N; i++) {
			cin >> window1[i][0];
			window1[i][1] = 0;
			window1[i][2] = -1;
		}
		for (int i = 0; i < M; i++) {
			cin >> window2[i][0];
			window2[i][1] = 0;
			window2[i][2] = -1;
		}
		for (int i = 0; i < K; i++)
			cin >> person[i];

		int cnt = K, t = 0;
		while (cnt > 0) {
			//정비 창구 완료
			for (int i = 0; i < M; i++) {
				if (window2[i][0] == window2[i][1]) {
					cnt--;
					window2[i][1] = 0;
					window2[i][2] = -1;
				}
			}

			//접수 창구 완료
			for (int i = 0; i < N; i++) {
				if (window1[i][0] == window1[i][1]) {
					window1[i][1] = 0;
					wait2.push(window1[i][2]);
					window1[i][2] = -1;
				}
			}

			//정비 창구 받기, 기록
			if (!wait2.empty()) {
				for (int i = 0; i < M; i++) {
					//비어있다면
					if (window2[i][2] == -1) {
						window2[i][2] = wait2.front();
						used[window2[i][2]][1] = i;		//기록
						wait2.pop();
					}
					if (wait2.empty())break;
				}
			}

			//사람 도착 확인
			for (int i = 0; i < K; i++) {
				if (person[i] == t)		//도착했다면, push
					wait1.push(-i);
			}

			//접수 창구 받기
			if (!wait1.empty()) {
				for (int i = 0; i < N; i++) {
					if (window1[i][2] == -1) {
						window1[i][2] = -wait1.top();
						used[window1[i][2]][0] = i;
						wait1.pop();
					}
					if (wait1.empty())break;
				}
			}

			t++;	//시간 증가
					//창구 진행 시간 증가
			for (int i = 0; i < N; i++)	if (window1[i][2] != -1) window1[i][1]++;
			for (int i = 0; i < M; i++) if (window2[i][2] != -1) window2[i][1]++;
		}

		int rst = 0;
		for (int i = 0; i < K; i++) {
			if (used[i][0] == A - 1 && used[i][1] == B - 1)
				rst += i + 1;
		}
		if (rst == 0)
			rst = -1;
		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}