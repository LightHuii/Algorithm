#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 21
int N;
long long K;
int cmp[MAX];	//2�� �� ����ϴ� �Է�
int ary[MAX];	//1�� �� ���� ���
bool visited[MAX];

//���丮�� ���ϱ�
long long fac(long long n) {
	if (n <= 1)return 1;

	return n * fac(n - 1);
}

void func1(int n, long long k) {
	//���� ����
	if (n == 0) {
		for (int i = 0; i < N; i++)
			cout << ary[i] << ' ';
		cout << endl;
		return;
	}

	long long tmp_fac = fac((long long)n - 1);	//n-1�� fac
	long long tmp = 0;	//tmp_fac�� ���
	long long cnt = 0;	//����ִ� visit�� ��
	//k���� Ŀ�� ���� cnt�� ã�Ƴ���
	while (k > tmp) {
		tmp += tmp_fac;
		cnt++;
	}

	//visited���� cnt��°�� ����ִ� �� num ã��
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

	//���� n-1�� ���� k - (tmp - tmp_fac)��°�� ã�´�
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
			long long tmp_fac = fac((long long)i - 1);	//n-1�� fac
			int cnt = 0, idx = cmp[N - i];

			//idx���� ���� ���� ���� ���� ������� ���� ������ ���Ѵ�.
			while (idx > 0)
				if (!visited[idx--])cnt++;
			sum += tmp_fac * (cnt-1);	//�׸�ŭ �踦 ���Ѵ�
			visited[cmp[N - i]] = true;
		}
		cout << sum + 1 << endl;	//���� ������ i�� 0�� �� ��츦 �����ش�
	}

	return 0;
}