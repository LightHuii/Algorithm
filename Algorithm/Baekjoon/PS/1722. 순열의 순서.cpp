#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 21
int N;
long long K;
int cmp[MAX];	//2일 때 사용하는 입력
int ary[MAX];	//1일 때 수열 결과
bool visited[MAX];

//팩토리얼 구하기
long long fac(long long n) {
	if (n <= 1)return 1;

	return n * fac(n - 1);
}

void func1(int n, long long k) {
	//기저 조건
	if (n == 0) {
		for (int i = 0; i < N; i++)
			cout << ary[i] << ' ';
		cout << endl;
		return;
	}

	long long tmp_fac = fac((long long)n - 1);	//n-1의 fac
	long long tmp = 0;	//tmp_fac의 배수
	long long cnt = 0;	//비어있는 visit의 수
	//k보다 커질 때의 cnt를 찾아낸다
	while (k > tmp) {
		tmp += tmp_fac;
		cnt++;
	}

	//visited에서 cnt번째로 비어있는 수 num 찾기
	int num = 1, cnt_tmp = 0;
	while (1) {
		if (!visited[num]) {
			cnt_tmp++;
			if (cnt_tmp == cnt)break;
		}
		num++;
	}
	visited[num] = true;
	ary[N - n] = num;

	//다음 n-1에 대해 k - (tmp - tmp_fac)번째를 찾는다
	func1(n - 1, k - (tmp - tmp_fac));
}

int main()
{
	int num;
	cin >> N >> num;

	if (num == 1) {
		cin >> K;
		
		func1(N, K);
	}
	else {
		for (int i = 0; i < N; i++)
			cin >> cmp[i];

		long long sum = 0;
		for (int i = N; i > 0; i--) {
			long long tmp_fac = fac((long long)i - 1);	//n-1의 fac
			int cnt = 0, idx = cmp[N - i];

			//idx보다 작은 수에 대해 아직 수행되지 않은 개수를 구한다.
			while (idx > 0)
				if (!visited[idx--])cnt++;
			sum += tmp_fac * (cnt-1);	//그만큼 배를 더한다
			visited[cmp[N - i]] = true;
		}
		cout << sum + 1 << endl;	//가장 마지막 i가 0일 때 경우를 더해준다
	}

	return 0;
}