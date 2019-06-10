#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string>
using namespace std;

#define MAX 12
int T, N;
int num[MAX];
int ma, mi;
string str;
int opernum[MAX - 1];
char op[4] = { '+', '-', '*', '/' };

void dfs(int idx) {
	if (idx == N - 1) {
		/*for (int i = 0; i < N - 1; i++)
		cout << str[i] << ' ';
		cout << endl;*/

		//계산
		int tmp = num[0];
		for (int i = 0; i < N - 1; i++) {
			if (str[i] == '+')
				tmp += num[i + 1];
			else if (str[i] == '-')
				tmp -= num[i + 1];
			else if (str[i] == '*')
				tmp *= num[i + 1];
			else if (str[i] == '/')
				tmp /= num[i + 1];
		}

		ma = max(ma, tmp);
		mi = min(mi, tmp);
		return;
	}



	for (int i = 0; i < 4; i++) {
		//해당 연산자를 모두 사용했다면 continue
		if (opernum[i] == 0)continue;
		opernum[i]--;		//한 번 감소 후 str[idx]에 삽입
		str[idx] = op[i];

		dfs(idx + 1);
		opernum[i]++;
	}
}

int main() {
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		cin >> N;
		ma = INT32_MIN;
		mi = INT32_MAX;
		str.clear();
		str.resize(N - 1);

		for (int i = 0; i < 4; i++)
			cin >> opernum[i];
		for (int i = 0; i < N; i++)
			cin >> num[i];

		dfs(0);

		cout << '#' << T - Ttmp << ' ' << ma - mi << endl;
	}

	return 0;
}