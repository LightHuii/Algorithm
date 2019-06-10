#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 11
int N;
int num[MAX];
int oper[4];
int ma = INT32_MIN;
int mi = INT32_MAX;
char selected[MAX - 1];

void dfs(int cnt) {
	if (cnt == N - 1) {
		//계산
		int rst = num[0];
		for (int i = 0; i < N - 1; i++) {
			if (selected[i] == '+')rst += num[i + 1];
			else if (selected[i] == '-')rst -= num[i + 1];
			else if (selected[i] == '*')rst *= num[i + 1];
			else if (selected[i] == '/')rst /= num[i + 1];
		}

		ma = max(ma, rst);
		mi = min(mi, rst);

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (oper[i] > 0) {	//하나라도 있으면
			if (i == 0)selected[cnt] = '+';
			else if (i == 1)selected[cnt] = '-';
			else if (i == 2)selected[cnt] = '*';
			else if (i == 3)selected[cnt] = '/';
			oper[i]--;
			dfs(cnt + 1);
			oper[i]++;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> num[i];
	for (int i = 0; i < 4; i++)
		cin >> oper[i];

	dfs(0);

	cout << ma << endl << mi << endl;
	return 0;
}