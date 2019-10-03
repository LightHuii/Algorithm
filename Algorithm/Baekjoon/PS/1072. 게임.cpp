#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1000000001		//10억
long long X, Y, Z;

int main(void)
{
	cin >> X >> Y;
	Z = (Y * 100) / X;	//처음 주어지는 승률
	if (Z >= 99) {		//승률이 99% 이상이면 더이상 바뀔 수 없다
		cout << -1 << endl;
		return 0;
	}

	//이분탐색
	long long l = 0, r = MAX;
	long long mid = 0;
	while (l <= r) {
		mid = (l + r) / 2;
		long long z = ((Y + mid) * 100) / (X + mid);

		//기준이 되는 승률 Z보다 크면 최대 범위를 줄인다.
		if (z > Z)
			r = mid - 1;
		//승률 Z와 같거나 작으면, 최소 범위를 늘린다.
		else
			l = mid + 1;
	}

	cout << l << endl;
	
	return 0;
}