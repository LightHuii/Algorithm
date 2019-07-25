#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1001
bool chae[MAX];

int N, K;

int main()
{
	int P, cnt = 0;
	int rst = 0;
	cin >> N >> K;

	while (1) {
		bool flag = false;
		for (int i = 2; i <= N; i++) {
			if (!chae[i]) {
				P = i;

				for (int j = P; j <= N; j += P) {
					if (chae[j])continue;
					chae[j] = true;
					cnt++;
					if (cnt == K) {
						rst = j;
						flag = false;
						break;
					}
					flag = true;
				}
				if (!flag)break;
			}
		}
		if (!flag)break;
	}

	cout << rst << endl;

	return 0;
}