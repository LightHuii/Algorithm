#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

#define NMAX 100
#define KMAX 10001
int n, k;
int dp1[KMAX] = { 0, };		//이전 dp 배열
int dp2[KMAX] = { 0, };		//다음 dp 배열
int coin[NMAX];

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> coin[i];

	//0포함 첫 동전의 배수는 모두 1가지라고 정한다.
	for (int i = 0; i <= k; i += coin[0])
		dp1[i] = 1;

	int cidx = 1;	//사용할 동전의 index

	while (cidx < n) {
		memset(dp2, 0, sizeof(dp2));		//dp2 초기화

		for (int i = 0; i <= k; i++) {
			//일단 dp2에 dp1을 복사(가짓 수 포함하므로)
			dp2[i] = dp1[i];

			//현재 동전 값이 만들고자 하는 값보다 같거나 작다면
			if (coin[cidx] <= i)
				dp2[i] += dp2[i - coin[cidx]];	//이전 dp를 더해준다
		}

		//다음 차례를 위해서 dp1에 dp2를 복사
		for (int i = 0; i <= k; i++)
			dp1[i] = dp2[i];
		
		cidx++;	//동전의 인덱스 증가
	}

	cout << dp1[k] << endl;	//n이 1일 경우 dp2는 모두 0이므로 dp1 기준

	return 0;
}