#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

int calendar[14] = { 0, };
int T;
int price[4];
int rst = INT32_MAX;
bool visited[12];

bool check() {
	for (int i = 0; i < 12; i++)
		if (calendar[i] != 0 && !visited[i])
			return false;
	return true;
}

void dfs(int sum, int idx) {
	if (sum > rst || idx > 13)return;
	if (check()) {
		rst = min(rst, sum);
		return;
	}

	if (idx > 0 && idx <= 12) {
		bool tmp[3];
		tmp[0] = calendar[idx - 1] != 0 && !visited[idx - 1];
		tmp[1] = calendar[idx] != 0 && !visited[idx];
		tmp[2] = calendar[idx + 1] != 0 && !visited[idx + 1];
		if (tmp[0] || tmp[1] || tmp[2]) {
			bool tmp2[3];
			tmp2[0] = visited[idx - 1];
			tmp2[1] = visited[idx];
			tmp2[2] = visited[idx + 1];
			if (tmp[0])
				visited[idx - 1] = true;
			if (tmp[1])
				visited[idx] = true;
			if (tmp[2])
				visited[idx + 1] = true;

			dfs(sum + price[2], idx + 1);

			visited[idx - 1] = tmp2[0];
			visited[idx] = tmp2[1];
			visited[idx + 1] = tmp2[2];

			//dfs(sum, idx + 1);
		}
	}
	if (calendar[idx] != 0 && !visited[idx]) {
		visited[idx] = true;
		dfs(sum + calendar[idx] * price[0], idx + 1);

		dfs(sum + price[1], idx + 1);
		visited[idx] = false;
	}
	dfs(sum, idx + 1);
}

int main() {
	cin >> T;
	int Ttmp = T;
	while (Ttmp--) {
		rst = INT32_MAX;
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < 4; i++)
			cin >> price[i];
		for (int i = 0; i < 12; i++)
			cin >> calendar[i];

		dfs(0, 0);

		rst = min(rst, price[3]);

		cout << '#' << T - Ttmp << ' ' << rst << endl;
	}

	return 0;
}
