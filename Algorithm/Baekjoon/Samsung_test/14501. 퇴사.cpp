#include<iostream>
#include<algorithm>
using namespace std;

#define MAX 16
int N;
int T[MAX];
int P[MAX];
bool selected[MAX];
int rst = 0;

void dfs(int day, int sum) {
	if (day == N + 1) {
		rst = max(rst, sum);
		return;
	}
	if (!selected[day]) {
		if (day + T[day] - 1 <= N) {
			for (int i = 0; i < T[day]; i++)
				selected[day + i] = true;

			dfs(day + T[day], sum + P[day]);

			for (int i = 0; i < T[day]; i++)
				selected[day + i] = false;
		}
	}
	dfs(day + 1, sum);
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> T[i] >> P[i];

	dfs(1, 0);

	cout << rst << endl;
	return 0;
}