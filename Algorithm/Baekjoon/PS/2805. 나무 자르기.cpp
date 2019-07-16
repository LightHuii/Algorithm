#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1000000

int N;
long long M;
long long ary[MAX] = { 0, };

long long bsch(long long start, long long end) {
	long long low = start;
	long long hi = end;
	long long rst = 0;

	while (low <= hi) {
		long long mid = (low + hi) / 2;
		long long tmp = 0;

		for (int i = 0; i < N; i++) {
			if (ary[i] - mid > 0)
				tmp += ary[i] - mid;
		}
		//cout << "tmp: " << tmp << endl;
		if (tmp < M) hi = mid - 1;
		else if (tmp > M) {
			rst = mid;
			low = mid + 1;
		}
		else return mid;
	}
	return rst;
}

int main() {
	long long ma = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> ary[i];
		ma = max(ma, ary[i]);
	}

	cout << bsch(1, ma) << endl;

	return 0;
}