#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

#define MAX 100000
long long ary[MAX] = { 0, };
long long tmp[MAX] = { 0, };
int N, S;

int main() {
	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> ary[i];

	int rst = INT32_MAX;
	int s = 0, e = 0;
	long long sum = ary[0];

	while (1) {
		// 현재 합이 아직 부족하므로
		if (sum < S) {
			e++;	//뒤의 수를 더해줌
			if (e >= N)break;	//인덱스가 끝나면 종료
			sum += ary[e];
		}
		else {
			rst = min(rst, e - s + 1);	//정답 후보
			sum -= ary[s];		//앞쪽 수를 빼준다.
			s++;
			if (s >= N)break;
		}
	}

	if (rst == INT32_MAX)
		cout << 0 << endl;
	else
		cout << rst << endl;

	return 0;
}