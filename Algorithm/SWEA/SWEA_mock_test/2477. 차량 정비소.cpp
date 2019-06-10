#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;

int T, N, M, K, A, B;
int person[1000];
int window1[20][3], window2[20][3];		//[0]: �ʿ��� ó���ð�, [1]: ���� ���� �ð�, [2]: ó������ ���num
int used[1000][2];		//[0]: ���� â�� ��ȣ, [1]: ���� â�� ��ȣ

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
			//���� â�� �Ϸ�
			for (int i = 0; i < M; i++) {
				if (window2[i][0] == window2[i][1]) {
					cnt--;
					window2[i][1] = 0;
					window2[i][2] = -1;
				}
			}

			//���� â�� �Ϸ�
			for (int i = 0; i < N; i++) {
				if (window1[i][0] == window1[i][1]) {
					window1[i][1] = 0;
					wait2.push(window1[i][2]);
					window1[i][2] = -1;
				}
			}

			//���� â�� �ޱ�, ���
			if (!wait2.empty()) {
				for (int i = 0; i < M; i++) {
					//����ִٸ�
					if (window2[i][2] == -1) {
						window2[i][2] = wait2.front();
						used[window2[i][2]][1] = i;		//���
						wait2.pop();
					}
					if (wait2.empty())break;
				}
			}

			//��� ���� Ȯ��
			for (int i = 0; i < K; i++) {
				if (person[i] == t)		//�����ߴٸ�, push
					wait1.push(-i);
			}

			//���� â�� �ޱ�
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

			t++;	//�ð� ����
					//â�� ���� �ð� ����
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