#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 1000001
int n;
bool chae[MAX];

void make_prime() {
	for (int i = 2; i < MAX; i++) {
		if (chae[i])continue;

		for (int j = i * 2; j < MAX; j += i) {
			if (chae[j])continue;
			chae[j] = true;
		}
	}
}

int main()
{
	make_prime();

	while (1) {
		scanf("%d", &n);
		if (n == 0)break;

		int x = 0, y = 0;

		for (int i = 3; i <= n; i++) {
			if (!chae[i] && !chae[n - i]) {
				x = i;
				y = n - i;
				break;
			}
		}
		printf("%d = %d + %d\n", n, x, y);
	}

	return 0;
}