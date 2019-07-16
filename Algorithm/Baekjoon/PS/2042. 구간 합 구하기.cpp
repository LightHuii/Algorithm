#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

#define MAX 1000001
int N, M, K;
int two = 1, n = 0;
long long tree[MAX * 4] = { 0, };	//넉넉하게 할당

int main() {
	cin >> N >> M >> K;

	//차수구하기
	while (N > two) {
		two *= 2;
		n++;
	}

	for (int i = 0; i < N; i++)
		cin >> tree[i + two];

	//나머지 노드(자식들의 합) 채워 넣기
	for (int i = two - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];

	long long a, b, c;
	long long rst = 0;
	while (M > 0 || K > 0) {
		cin >> a >> b >> c;
		if (a == 1) {
			M--;
			long long interv = c - tree[two + b - 1];		//차이
			for (long long i = two + b - 1; i > 0; i /= 2)
				tree[i] += interv;
		}
		else if (a == 2) {
			K--;
			rst = 0;
			long long l = two + b - 1;
			long long r = two + c - 1;

			// 인덱스가 어긋나면 끝
			while (l <= r) {
				//왼 쪽이 홀수면
				if (l % 2 != 0) {
					rst += tree[l];	//일단 값을 더하고
					l++;			//증가
				}

				//오른 쪽이 짝수면
				if (r % 2 == 0) {
					rst += tree[r];	//더하고
					r--;			//감소
				}

				//같으면 더 이상 올라갈 곳이 없으므로 끝
				if (l == r)
					break;

				//짝수, 홀수에 상관없이 올려준다.
				l /= 2;
				r /= 2;
			}
			cout << rst << endl;
		}
	}

	return 0;
}
